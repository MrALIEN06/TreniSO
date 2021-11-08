#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#include"trackList.h"
#include"file.h"
#include"track.h"

//#define DEBUG

void addTrackList(TRACKLIST *pTrackList, TRACK *pTrack) {
	TRACKLIST *pTmpTrackList = pTrackList;
	if(pTrackList->item==NULL) {
		pTrackList->item = pTrack;
		pTrackList->next = NULL;
	} else {
		while(pTmpTrackList->next != NULL){
			pTmpTrackList=pTmpTrackList->next;
		}
		pTmpTrackList->next = storeTrackList();
		pTmpTrackList->next->item = pTrack;
		pTmpTrackList->next->next = NULL;
	}
	#ifdef DEBUG
		printf("\n[Debug: addTrackList()]: %s:%d -> Aggiunto: %s alla lista binari",__FILE__,__LINE__,pTrack->name);
	#endif
}

TRACKLIST* storeTrackList() {
	TRACKLIST *pTmpTrackList = (TRACKLIST*)malloc(sizeof(TRACKLIST));
	if(pTmpTrackList==NULL) {
		printf("\n[ERROR: storeTrackList()] %s:%d -> Impossibile allocare memoria per la lista binari\n",__FILE__,__LINE__);
		perror("[ERROR malloc()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: storeTrackList()]: %s:%d -> Memoria allocata [%p] per lista binari",__FILE__,__LINE__,pTmpTrackList);
	#endif
	return pTmpTrackList;
}

TRACKLIST* getEmpityTrackList() {
	TRACKLIST *pTmpTrackList = storeTrackList();
	pTmpTrackList->item = NULL;
	pTmpTrackList->next = NULL;
	#ifdef DEBUG
		printf("\n[Debug: getEmpityTrackList()]: %s:%d -> Restituita lista binari vuota",__FILE__,__LINE__);
	#endif
	return pTmpTrackList;
}

void freeTrackList(TRACKLIST *pTrackList) {
	TRACKLIST *pTmpTrackList;
	while(pTrackList->next!=NULL){
		pTmpTrackList=pTrackList;
		pTrackList=pTrackList->next;
		free(pTmpTrackList);
	}
	free(pTrackList);
	#ifdef DEBUG
		printf("\n[Debug: freeTrackList()]: %s:%d -> Lista binari deallocata",__FILE__,__LINE__);
	#endif
}

TRACK* searchTrackList(TRACKLIST *pTrackList, char *pName) {
	TRACKLIST *pTmpTrackList = pTrackList;
	while(strcmp(pTmpTrackList->item->name,pName)){
		if(pTmpTrackList->next==NULL) {
			printf("\n[ERROR: searchTrackList()] %s:%d -> Binario non trovato nella lista",__FILE__,__LINE__);
			exit(EXIT_FAILURE);
		}
		pTmpTrackList = pTmpTrackList->next;
	}
	#ifdef DEBUG
		printf("\n[Debug: searchTrackList()]: %s:%d -> Binario %s trovato nella lista",__FILE__,__LINE__,pName);
	#endif
	return pTmpTrackList->item;
}

void statusTrackList(TRACKLIST *pTrackList) {
	TRACKLIST *pTmpTrackList = pTrackList;
	if(pTmpTrackList->item != NULL) {
		statusTrack(pTmpTrackList->item);
		while(pTmpTrackList->next!=NULL){
			pTmpTrackList = pTmpTrackList->next;
			statusTrack(pTmpTrackList->item);
		}
	}
}

void showTrackList(TRACKLIST *pTrackList) {
	TRACKLIST *pTmpTrackList = pTrackList;
	if(pTmpTrackList->item!=NULL) {
		printf("%s ",pTmpTrackList->item->name);
		while(pTmpTrackList->next!=NULL){
			pTmpTrackList = pTmpTrackList->next;
			printf("%s ",pTmpTrackList->item->name);
		}
	} else {
		printf("NULL");
	}
}
