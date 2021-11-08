#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<signal.h>
#include<sys/socket.h>
#include<errno.h>

#include"ETCS2.h"
#include"railway.h"
#include"socket.h"
#include"trackList.h"
#include"train.h"

//#define DEBUG

#define GO 0
#define STOP -1
#define TIME_SLEEP 3

void ETCS2() {
	signal(SIGUSR1,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	newRailway();
	forkETCS2();
	sleep(1);
	if(killpg(0,SIGUSR1)==-1){
		printf("\n[ERROR: ETCS2()] %s:%d -> Impossibile far continuare i fork\n",__FILE__,__LINE__);
		perror("[ERROR killpg()]");
		exit(EXIT_FAILURE);
	}
	int status;
	while(wait(&status)>0) {
		if(status!=EXIT_SUCCESS) {
			printf("\n[ERROR: ETCS2] %s:%d -> Interruzione esecuzione programma\n",__FILE__,__LINE__);
			if(killpg(0,SIGTERM)==-1){
				printf("\n[ERROR: ETCS2] %s:%d -> Impossibile interrompere l'esecuzione del programma\n",__FILE__,__LINE__);
				perror("[ERROR killpg()]");
				exit(EXIT_FAILURE);
			}
		}
	}
	freeRailway();
	#ifdef DEBUG
		printf("\n[Debug: ETCS2()]: %s:%d -> Esecuzione ETCS2 terminata",__FILE__,__LINE__);
	#endif
}

void forkETCS2() {
	TRAIN *pTrainList[5];
	pTrainList[0] = newTrain("T1");
	pTrainList[1] = newTrain("T2");
	pTrainList[2] = newTrain("T3");
	pTrainList[3] = newTrain("T4");
	pTrainList[4] = newTrain("T5");
	for(int count=0;count<5;count++) {
		sendTrainItinerary(pTrainList[count]);
	}
	pid_t pid;
	for(int count=0;count<5;count++) {
		pid = fork();
		if(pid==0) {
			loopETCS2(pTrainList[count]);
		}
		if(pid<0) {
			printf("\n[ERROR: forkETCS2()] %s:%d -> Impossibile eseguire fork\n",__FILE__,__LINE__);
			perror("[ERROR fork()]");
			exit(EXIT_FAILURE);
		}
	}
	#ifdef DEBUG
		printf("\n[Debug: forkETCS2()]: %s:%d -> Fork eseguiti",__FILE__,__LINE__);
	#endif
}

void sendTrainItinerary(TRAIN *pTrain) {
	TRACKLIST *pTrainPath = pTrain->path;
	int sock = openClient();
	requestConnect(sock);
	writeSocket(sock,pTrainPath->item->name);
	free(readSocket(sock));
	while(pTrainPath->next!=NULL) {
		pTrainPath = pTrainPath->next;
		writeSocket(sock,pTrainPath->item->name);
		free(readSocket(sock));
	}
	closeSocket(sock);
	#ifdef DEBUG
		printf("\n[Debug: sendTrainItinerary()]: %s:%d -> Itinerario treno %s inviato",__FILE__,__LINE__,pTrain->name);
	#endif
}

void loopETCS2(TRAIN *pTrain) {
	signal(SIGUSR1,sigContinueETCS2);
	signal(SIGTERM,SIG_DFL);
	pause();
	int sock;
	int flag = 1;
	while(flag) {
		sock = openClient();
		requestConnect(sock);
		writeSocket(sock,pTrain->name);
		if(readIntSocket(sock)==GO) {
			flag = moveETCS2(pTrain);
			writeIntSocket(sock,GO);
		} else {
			lockTrain(pTrain);
		}
		closeSocket(sock);
		sleep(TIME_SLEEP);
	}
	#ifdef DEBUG
		printf("\n[Debug: loopETCS2()]: %s:%d -> Loop di %s terminato",__FILE__,__LINE__,pTrain->name);
	#endif
	freeTrain(pTrain);
	exit(EXIT_SUCCESS);
}

int moveETCS2(TRAIN *pTrain) {
	#ifdef DEBUG
		printf("\n[Debug: moveETCS2()]: %s:%d -> Riciesta di movimento di %s",__FILE__,__LINE__,pTrain->name);
	#endif
	if(pTrain->position==NULL){
		startTrain(pTrain);
		return 1;
	}
	searchTrackList(pTrain->position->near,pTrain->itinerary->item->name);/*CONTROLLO CHE IL PROSSIMO BINARIO SIA FRA I VICINI DI QUELLO CORRENTE*/
	if(pTrain->itinerary->next==NULL) {
		stopTrain(pTrain);
		return 0;
	}
	moveTrain(pTrain);
	return 1;
}

void sigContinueETCS2(int signal) {
	#ifdef DEBUG
		printf("\n[Debug: sigContinueETCS2()]: %s:%d -> Segnale d'avvio ricevuto",__FILE__,__LINE__);
	#endif
}
