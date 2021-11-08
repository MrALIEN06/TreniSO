#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<signal.h>
#include<errno.h>

#include"ETCS1.h"
#include"file.h"
#include"railway.h"
#include"trackList.h"
#include"train.h"

//#define DEBUG

#define TIME_SLEEP 3

void ETCS1() {
	signal(SIGUSR1,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	int status;
	newRailway();
	forkETCS1();
	sleep(1);
	if(killpg(0,SIGUSR1)==-1){
		printf("\n[ERROR: ETCS1] %s:%d -> Impossibile far continuare i fork\n",__FILE__,__LINE__);
		perror("[ERROR killpg()]");
		exit(EXIT_FAILURE);
	}
	while(wait(&status)>0) {
		if(status!=EXIT_SUCCESS) {
			printf("\n[ERROR: ETCS1] %s:%d -> Interruzione esecuzione programma\n",__FILE__,__LINE__);
			if(killpg(0,SIGTERM)==-1){
				printf("\n[ERROR: ETCS1] %s:%d -> Interruzione esecuzione programma non riuscita\n",__FILE__,__LINE__);
				perror("[ERROR killpg()]");
				exit(EXIT_FAILURE);
			}
		}
	}
	freeRailway();
	#ifdef DEBUG
		printf("\n[Debug: ETCS1()]: %s:%d -> Esecuzione ETCS1 terminata",__FILE__,__LINE__);
	#endif
}

void forkETCS1() {
	TRAIN *pTrainList[5];
	pTrainList[0] = newTrain("T1");
	pTrainList[1] = newTrain("T2");
	pTrainList[2] = newTrain("T3");
	pTrainList[3] = newTrain("T4");
	pTrainList[4] = newTrain("T5");
	pid_t pid;
	for(int count=0;count<5;count++) {
		pid = fork();
		if(pid==0) {
			loopETCS1(pTrainList[count]);
		}
		if(pid<0) {
			printf("\n[ERROR: forkETCS1()] %s:%d -> Impossibile eseguire fork\n",__FILE__,__LINE__);
			perror("[ERROR fork()]");
			exit(EXIT_FAILURE);
		}
	}
	#ifdef DEBUG
		printf("\n[Debug: forkETCS1()]: %s:%d -> Fork eseguiti",__FILE__,__LINE__);
	#endif
}

void loopETCS1(TRAIN *pTrain) {
	signal(SIGUSR1,sigContinueETCS1);
	signal(SIGTERM,SIG_DFL);
	pause();
	int flag = 1;
	while(flag) {
		flag = moveETCS1(pTrain);
		sleep(TIME_SLEEP);
	}
	#ifdef DEBUG
		printf("\n[Debug: loopETCS1()]: %s:%d -> Loop di %s terminato",__FILE__,__LINE__,pTrain->name);
	#endif
	freeTrain(pTrain);
	exit(EXIT_SUCCESS);
}

int moveETCS1(TRAIN *pTrain) {
	#ifdef DEBUG
		printf("\n[Debug: moveETCS1()]: %s:%d -> Riciesta di movimento di %s",__FILE__,__LINE__,pTrain->name);
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
	if(readIntFile(pTrain->itinerary->item->file)==0) {
		moveTrain(pTrain);
	} else {
		lockTrain(pTrain);
	}
	return 1;
}

void sigContinueETCS1(int signal) {
	#ifdef DEBUG
		printf("\n[Debug: sigContinueETCS1()]: %s:%d -> Segnale d'avvio ricevuto",__FILE__,__LINE__);
	#endif
}
