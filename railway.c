#include<stdlib.h>
#include<stdio.h>

#include"railway.h"
#include"trackList.h"
#include"track.h"

//#define DEBUG

TRACKLIST *railway;

void newRailway() {
	TRACK *S1,*S2,*S3,*S4,*S5,*S6,*S7,*S8,*MA1,*MA2,*MA3,*MA4,*MA5,*MA6,*MA7,*MA8,*MA9,*MA10,*MA11,*MA12,*MA13,*MA14,*MA15,*MA16;
	S1 = newTrack("S1");
	S2 = newTrack("S2");
	S3 = newTrack("S3");
	S4 = newTrack("S4");
	S5 = newTrack("S5");
	S6 = newTrack("S6");
	S7 = newTrack("S7");
	S8 = newTrack("S8");
	MA1 = newTrack("MA1");
	MA2 = newTrack("MA2");
	MA3 = newTrack("MA3");
	MA4 = newTrack("MA4");
	MA5 = newTrack("MA5");
	MA6 = newTrack("MA6");
	MA7 = newTrack("MA7");
	MA8 = newTrack("MA8");
	MA9 = newTrack("MA9");
	MA10 = newTrack("MA10");
	MA11 = newTrack("MA11");
	MA12 = newTrack("MA12");
	MA13 = newTrack("MA13");
	MA14 = newTrack("MA14");
	MA15 = newTrack("MA15");
	MA16 = newTrack("MA16");
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
	railway = getEmpityTrackList();
	addTrackList(railway,S1);
	addTrackList(railway,S2);
	addTrackList(railway,S3);
	addTrackList(railway,S4);
	addTrackList(railway,S5);
	addTrackList(railway,S6);
	addTrackList(railway,S7);
	addTrackList(railway,S8);
	addTrackList(railway,MA1);
	addTrackList(railway,MA2);
	addTrackList(railway,MA3);
	addTrackList(railway,MA4);
	addTrackList(railway,MA5);
	addTrackList(railway,MA6);
	addTrackList(railway,MA7);
	addTrackList(railway,MA8);
	addTrackList(railway,MA9);
	addTrackList(railway,MA10);
	addTrackList(railway,MA11);
	addTrackList(railway,MA12);
	addTrackList(railway,MA13);
	addTrackList(railway,MA14);
	addTrackList(railway,MA15);
	addTrackList(railway,MA16);
	#ifdef DEBUG
		printf("\n[Debug: newRailway()]: %s:%d -> Ferrovia generata",__FILE__,__LINE__);
	#endif
}

void freeRailway() {
	TRACKLIST *pTrackList;
	while(railway->next!=NULL){
		pTrackList=railway;
		railway=railway->next;
		freeTrack(pTrackList->item);
		free(pTrackList);
	}
	freeTrack(railway->item);
	free(railway);
	#ifdef DEBUG
		printf("\n[Debug: freeRailway()]: %s:%d -> Ferrovia deallocata",__FILE__,__LINE__);
	#endif
}

TRACK* searchInARailway(char *pName) {
	#ifdef DEBUG
		printf("\n[Debug: searchInARailway()]: %s:%d -> Cerco binario %s nella ferrovia",__FILE__,__LINE__,pName);
	#endif
	return searchTrackList(railway,pName);
}
