#include<stdlib.h>
#include<stdio.h>

#include"virtual.h"
#include"track.h"
#include"train.h"

//#define DEBUG

TRACKLIST *virtualRailway;

TRACK* newVirtualTrack(char *pName) {
 	TRACK *pTrack = storeTrack();
	pTrack->name = pName;
	pTrack->near = getEmpityTrackList();
	pTrack->file = 0;
	#ifdef DEBUG
		printf("\n[Debug: newVirtualTrack()]: %s:%d -> Binario virtuale:%s Memoria:[%p]",__FILE__,__LINE__,pName,pTrack);
	#endif
	return pTrack;
}

void freeVirtualTrack(TRACK *pTrack) {
	freeTrackList(pTrack->near);
	#ifdef DEBUG
		printf("\n[Debug: freeVirtualTrack()]: %s:%d -> Binario virtuale %s [%p] deallocato",__FILE__,__LINE__,pTrack->name,pTrack);
	#endif
	free(pTrack);
}

TRAIN* newVirtualTrain(char *pName) {
	TRAIN *pTrain = storeTrain();
	pTrain->name = pName;
	pTrain->position = NULL;
	pTrain->log = 0;
	pTrain->path = NULL;
	pTrain->itinerary = NULL;
	#ifdef DEBUG
		printf("\n[Debug: newVirtualTrain()]: %s:%d -> Treno virtuale:%s Memoria:[%p] ",__FILE__,__LINE__,pName,pTrain);
	#endif
	return pTrain;
}

void freeVirtualTrain(TRAIN *pTrain) {
	freeTrackList(pTrain->path);
	#ifdef DEBUG
		printf("\n[Debug: freeVirtualTrain()]: %s:%d -> Treno virtuale %s deallocato",__FILE__,__LINE__,pTrain->name);
	#endif
	free(pTrain);
}

void newVirtualRailway() {
	TRACK *S1,*S2,*S3,*S4,*S5,*S6,*S7,*S8,*MA1,*MA2,*MA3,*MA4,*MA5,*MA6,*MA7,*MA8,*MA9,*MA10,*MA11,*MA12,*MA13,*MA14,*MA15,*MA16;
	S1 = newVirtualTrack("S1");
	S2 = newVirtualTrack("S2");
	S3 = newVirtualTrack("S3");
	S4 = newVirtualTrack("S4");
	S5 = newVirtualTrack("S5");
	S6 = newVirtualTrack("S6");
	S7 = newVirtualTrack("S7");
	S8 = newVirtualTrack("S8");
	MA1 = newVirtualTrack("MA1");
	MA2 = newVirtualTrack("MA2");
	MA3 = newVirtualTrack("MA3");
	MA4 = newVirtualTrack("MA4");
	MA5 = newVirtualTrack("MA5");
	MA6 = newVirtualTrack("MA6");
	MA7 = newVirtualTrack("MA7");
	MA8 = newVirtualTrack("MA8");
	MA9 = newVirtualTrack("MA9");
	MA10 = newVirtualTrack("MA10");
	MA11 = newVirtualTrack("MA11");
	MA12 = newVirtualTrack("MA12");
	MA13 = newVirtualTrack("MA13");
	MA14 = newVirtualTrack("MA14");
	MA15 = newVirtualTrack("MA15");
	MA16 = newVirtualTrack("MA16");
	virtualRailway = getEmpityTrackList();
	addTrackList(virtualRailway,S1);
	addTrackList(virtualRailway,S2);
	addTrackList(virtualRailway,S3);
	addTrackList(virtualRailway,S4);
	addTrackList(virtualRailway,S5);
	addTrackList(virtualRailway,S6);
	addTrackList(virtualRailway,S7);
	addTrackList(virtualRailway,S8);
	addTrackList(virtualRailway,MA1);
	addTrackList(virtualRailway,MA2);
	addTrackList(virtualRailway,MA3);
	addTrackList(virtualRailway,MA4);
	addTrackList(virtualRailway,MA5);
	addTrackList(virtualRailway,MA6);
	addTrackList(virtualRailway,MA7);
	addTrackList(virtualRailway,MA8);
	addTrackList(virtualRailway,MA9);
	addTrackList(virtualRailway,MA10);
	addTrackList(virtualRailway,MA11);
	addTrackList(virtualRailway,MA12);
	addTrackList(virtualRailway,MA13);
	addTrackList(virtualRailway,MA14);
	addTrackList(virtualRailway,MA15);
	addTrackList(virtualRailway,MA16);
	linkTrack(S1,MA1);
	linkTrack(MA1,MA2);
	linkTrack(MA2,MA3);
	linkTrack(MA3,MA4);
	linkTrack(MA4,S5);
	linkTrack(S2,MA5);
	linkTrack(MA5,MA6);
	linkTrack(MA6,MA7);
	linkTrack(MA7,MA3);
	linkTrack(MA3,MA8);
	linkTrack(MA8,S6);
	linkTrack(S3,MA9);
	linkTrack(MA9,MA10);
	linkTrack(MA10,MA11);
	linkTrack(MA11,MA12);
	linkTrack(MA12,MA13);
	linkTrack(MA13,S7);
	linkTrack(S4,MA14);
	linkTrack(MA14,MA15);
	linkTrack(MA15,MA16);
	linkTrack(MA16,MA12);
	linkTrack(MA12,S8);
	#ifdef DEBUG
		printf("\n[Debug: newVirtualRailway()]: %s:%d -> Ferrovia virtuale generata",__FILE__,__LINE__);
	#endif
}

void freeVirtualRailway() {
	TRACKLIST *pTrackList;
	while(virtualRailway->next!=NULL){
		pTrackList=virtualRailway;
		virtualRailway=virtualRailway->next;
		freeVirtualTrack(pTrackList->item);
		free(pTrackList);
	}
	freeVirtualTrack(virtualRailway->item);
	free(virtualRailway);
	#ifdef DEBUG
		printf("\n[Debug: freeVirtualRailway()]: %s:%d -> Ferrovia virtuale deallocata",__FILE__,__LINE__);
	#endif
}

TRACK* searchInAVirtualRailway(char *pName) {
	#ifdef DEBUG
		printf("\n[Debug: searchInAVirtualRailway()]: %s:%d -> Cerco binario %s nella ferrovia virtuale",__FILE__,__LINE__,pName);
	#endif
	return searchTrackList(virtualRailway,pName);
}
