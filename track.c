#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#include"track.h"
#include"file.h"
#include"trackList.h"

//#define DEBUG

#define FILE_DIR "file/binari/"

TRACK* newTrack(char *pName) {
	char file[FILENAME_MAX] = FILE_DIR;
 	TRACK *pTrack = storeTrack();
	pTrack->name = pName;
	pTrack->near = getEmpityTrackList();
	pTrack->file = createFile(strcat(file,pName));
	writeFile(pTrack->file,"0");
	#ifdef DEBUG
		printf("\n[Debug: newTrack()]: %s:%d -> Binario:%s File:%d Memoria:[%p]",__FILE__,__LINE__,pName,pTrack->file,pTrack);
	#endif
	return pTrack;
}

TRACK* storeTrack() {
	TRACK *pTrack = (TRACK*)malloc(sizeof(TRACK));
	if(pTrack==NULL) {
		printf("\n[ERROR: storeTrack()] %s:%d -> Impossibile allocare memoria per il binario\n",__FILE__,__LINE__);
		perror("[ERROR malloc()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: storeTrack()]: %s:%d -> Memoria allocata [%p] per il binario",__FILE__,__LINE__,pTrack);
	#endif
	return pTrack;
}

void linkTrack(TRACK* pTrack1, TRACK* pTrack2) {
	addTrackList(pTrack1->near,pTrack2);
	addTrackList(pTrack2->near,pTrack1);
	#ifdef DEBUG
		printf("\n[Debug: linkTrack()]: %s:%d -> Link binari %s<->%s ",__FILE__,__LINE__,pTrack1->name,pTrack2->name);
	#endif
}

void freeTrack(TRACK *pTrack) {
	closeFile(pTrack->file);
	freeTrackList(pTrack->near);
	#ifdef DEBUG
		printf("\n[Debug: freeTrack()]: %s:%d -> Binario %s [%p] deallocato",__FILE__,__LINE__,pTrack->name,pTrack);
	#endif
	free(pTrack);
}

void statusTrack(TRACK *pTrack) {
	printf("\n\tNome: %s",pTrack->name);
	printf("\tFile: %d ",pTrack->file);
	printf("\tVicini: ");
	showTrackList(pTrack->near);
}
