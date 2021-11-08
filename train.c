#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"train.h"
#include"file.h"
#include"railway.h"

//#define DEBUG

#define LOG_DIR "file/log/"
#define TRK_DIR "file/itinerari/"

TRAIN* newTrain(char *pName) {
	char logPath[FILENAME_MAX] = LOG_DIR;
	char trkPath[FILENAME_MAX] = TRK_DIR;
	TRAIN *pTrain = storeTrain();
	pTrain->name = pName;
	pTrain->position = NULL;
	pTrain->log = createFile(strcat(strcat(logPath,pName),".log"));
	pTrain->path = getTrainItinerary(strcat(trkPath,pName));
	pTrain->itinerary = pTrain->path;
	#ifdef DEBUG
		writeFile(pTrain->log,"CREATE-->");
		writeTrainLog(pTrain);
		printf("\n[Debug: newTrain()]: %s:%d -> Treno:%s File:%d Memoria:[%p] Itinerario/Cammino: ",__FILE__,__LINE__,pName,pTrain->log,pTrain);
		showTrackList(pTrain->path);
	#endif
	return pTrain;
}

TRAIN* storeTrain() {
	TRAIN *pTrain = (TRAIN*)malloc(sizeof(TRAIN));
	if(pTrain==NULL) {
		printf("\n[ERROR: storeTrain()] %s:%d -> Impossibile allocare memoria per il treno\n",__FILE__,__LINE__);
		perror("[ERROR malloc()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: storeTrain()]: %s:%d -> Memoria allocata [%p] per il treno",__FILE__,__LINE__,pTrain);
	#endif
	return pTrain;
}

void startTrain(TRAIN *pTrain) {
	int number = readIntFile(pTrain->itinerary->item->file);
	writeIntFile(pTrain->itinerary->item->file,++number);
	pTrain->position = pTrain->itinerary->item;
	pTrain->itinerary = pTrain->itinerary->next;
	writeFile(pTrain->log,"START--->");
	writeTrainLog(pTrain);
	#ifdef DEBUG
		printf("\n[Debug: startTrain()]: %s:%d -> [START] Treno:%s Binario:%s",__FILE__,__LINE__,pTrain->name,pTrain->position->name);
	#endif
}

void moveTrain(TRAIN *pTrain) {
	writeIntFile(pTrain->position->file,0);
	writeIntFile(pTrain->itinerary->item->file,1);
	pTrain->position = pTrain->itinerary->item;
	pTrain->itinerary = pTrain->itinerary->next;
	writeFile(pTrain->log,"MOVE---->");
	writeTrainLog(pTrain);
	#ifdef DEBUG
		printf("\n[Debug: moveTrain()]: %s:%d -> [MOVIMENTO] Treno:%s Binario:%s ",__FILE__,__LINE__,pTrain->name,pTrain->position->name);
	#endif
}

void stopTrain(TRAIN *pTrain) {
	int number = (char)readIntFile(pTrain->itinerary->item->file);
	writeIntFile(pTrain->itinerary->item->file,++number);
	writeIntFile(pTrain->position->file,0);
	pTrain->position = pTrain->itinerary->item;
	pTrain->itinerary = NULL;
	writeFile(pTrain->log,"STOP---->");
	writeTrainLog(pTrain);
	#ifdef DEBUG
		printf("\n[Debug: stopTrain()]: %s:%d -> [STOP] Treno:%s Binario:%s ",__FILE__,__LINE__,pTrain->name,pTrain->position->name);
	#endif
}

void lockTrain(TRAIN *pTrain) {
	writeFile(pTrain->log,"LOCK---->");
	writeTrainLog(pTrain);
	#ifdef DEBUG
		printf("\n[Debug: lockTrain()]: %s:%d -> [STALLO] Treno:%s Binario:%s ",__FILE__,__LINE__,pTrain->name,pTrain->position->name);
	#endif
}

void freeTrain(TRAIN *pTrain) {
	closeFile(pTrain->log);
	freeTrackList(pTrain->path);
	#ifdef DEBUG
		printf("\n[Debug: freeTrain()]: %s:%d -> Treno %s deallocato",__FILE__,__LINE__,pTrain->name);
	#endif
	free(pTrain);
}

TRACKLIST* getTrainItinerary(char *pFilePath) {
	TRACKLIST *pTmpTrackList = getEmpityTrackList();
	int file = openFile(pFilePath);
	char *pString  = readFile(file);
	for(char *pChar=strtok(pString,", ");pChar!=NULL;pChar=strtok(NULL,", ")) {
		addTrackList(pTmpTrackList,searchInARailway(pChar));
	}
	closeFile(file);
	free(pString);
	#ifdef DEBUG
		printf("\n[Debug: getTrainItinerary()]: %s:%d -> Itinerario treno: ",__FILE__,__LINE__);
		showTrackList(pTmpTrackList);
	#endif
	return pTmpTrackList;
}

void writeTrainLog(TRAIN *pTrain) {
	writeFile(pTrain->log,"  [Attuale: ");
	if(pTrain->position!=NULL) {
		writeFile(pTrain->log,pTrain->position->name);
	} else {
		writeFile(pTrain->log,"---");
	}
	writeFile(pTrain->log,"]\t[Prossima: ");
	if(pTrain->itinerary!=NULL) {
		writeFile(pTrain->log,pTrain->itinerary->item->name);

	} else {
		writeFile(pTrain->log,"---");
	}
	writeFile(pTrain->log,"]  \t");
	writeTime(pTrain->log);
	#ifdef DEBUG
		printf("\n[Debug: writeTrainLog()]: %s:%d -> Scritto nel log di %s ",__FILE__,__LINE__,pTrain->name);
	#endif
}

void statusTrain(TRAIN *pTrain) {
	printf("\n\tNome: %s",pTrain->name);
	printf("\tLogFile: %d ",pTrain->log);
	printf("\tPosizione: ");
	if(pTrain->position != NULL) {
		printf("%s",pTrain->position->name);
	} else {
		printf("NULL");
	}
	printf("\tCammino: ");
	if(pTrain->itinerary != NULL) {
		showTrackList(pTrain->itinerary);
	} else {
		printf("NULL");
	}
	printf("\tItinerario: ");
	showTrackList(pTrain->path);
}
