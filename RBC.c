#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"RBC.h"
#include"file.h"
#include"socket.h"
#include"virtual.h"
#include"trackList.h"
#include"train.h"

//#define DEBUG

#define LOG_DIR "file/log/RBC.log"
#define GO 0
#define STOP -1
#define N_TRAIN 5

void RBC() {
	TRAIN *pTrainList[5];
	pTrainList[0] = newVirtualTrain("T1");
	pTrainList[1] = newVirtualTrain("T2");
	pTrainList[2] = newVirtualTrain("T3");
	pTrainList[3] = newVirtualTrain("T4");
	pTrainList[4] = newVirtualTrain("T5");
	newVirtualRailway();
	int sock = openServer();
	int tmpSock;
	for(int count = 0;count<5;count++) {
		tmpSock = acceptConnect(sock);
		pTrainList[count]->path = recivedTrainItinerary(tmpSock);
		pTrainList[count]->itinerary = pTrainList[count]->path;
		closeSocket(tmpSock);
	}
	int file = createFile(LOG_DIR);
	int search,flag = 1;
	char *pString;
	while(flag) {
		tmpSock = acceptConnect(sock);
		pString = readSocket(tmpSock);
		for(search=0;strcmp(pTrainList[search]->name,pString);search++);
		flag = requestRBC(tmpSock,pTrainList[search],file);
		closeSocket(tmpSock);
	}
	closeFile(file);
	closeSocket(sock);
	freeVirtualRailway();
	#ifdef DEBUG
		printf("\n[Debug: RBC()]: %s:%d -> Esecuzione RBC terminata",__FILE__,__LINE__);
	#endif
}

TRACKLIST* recivedTrainItinerary(int sock) {
	char *pString;
	TRACKLIST *pItinerary = getEmpityTrackList();
	for(int count=0;count<2;) {
		pString = readSocket(sock);
		writeSocket(sock,"ok");
		if(strncmp(pString,"S\0",1)==0) {
			count++;
		}
		addTrackList(pItinerary,searchInAVirtualRailway(pString));
		free(pString);
	}
	#ifdef DEBUG
		printf("\n[Debug: recivedTrainItinerary()]: %s:%d -> Itinerario ricevuto: ",__FILE__,__LINE__);
		showTrackList(pItinerary);
	#endif
	return pItinerary;
}

int requestRBC(int sock,TRAIN *pTrain,int file) {
	static int count=0;
	char *pString = pTrain->itinerary->item->name;
	if(strncmp(pString,"S\0",1)==0) {
		writeRBCLog(file,pTrain,GO);
		moveRBC(sock,pTrain);
		count++;
	} else {
		if(pTrain->itinerary->item->file==0){
			writeRBCLog(file,pTrain,GO);
			moveRBC(sock,pTrain);
		} else {
			writeRBCLog(file,pTrain,STOP);
			writeIntSocket(sock,STOP);
		}
	}
	#ifdef DEBUG
		printf("\n[Debug: requestRBC()]: %s:%d -> Riciesta di movimento di %s valutata",__FILE__,__LINE__,pTrain->name);
	#endif
	if(count==N_TRAIN*2) {
		return 0;
	}
	return 1;
}

void moveRBC(int sock,TRAIN *pTrain) {
	writeIntSocket(sock,GO);
	readIntSocket(sock);
	if(pTrain->position!=NULL) {
		pTrain->position->file--;
	}
	pTrain->position = pTrain->itinerary->item;
	pTrain->position->file++;
	pTrain->itinerary = pTrain->itinerary->next;
	#ifdef DEBUG
		printf("\n[Debug: moveRBC()]: %s:%d -> Riciesta di movimento di %s accettata",__FILE__,__LINE__,pTrain->name);
	#endif
}

void writeRBCLog(int file,TRAIN *pTrain,int state) {
	writeFile(file,"[Treno: ");
	writeFile(file,pTrain->name);
	writeFile(file,"] [Attuale: ");
	if(pTrain->position!=NULL) {
		writeFile(file,pTrain->position->name);
	} else {
		writeFile(file,"---");
	}
	writeFile(file,"]\t[Richiesta: ");
	if(pTrain->itinerary!=NULL) {
		writeFile(file,pTrain->itinerary->item->name);
	} else {
		writeFile(file,"---");
	}
	if(state==GO) {
		writeFile(file,"] \t[Autorizzato: SI]\t");
	} else {
		writeFile(file,"] \t[Autorizzato: NO]\t");
	}
	writeTime(file);
	#ifdef DEBUG
		printf("\n[Debug: writeRBCLog()]: %s:%d -> Scritto nel log di RBC ",__FILE__,__LINE__);
	#endif
}
