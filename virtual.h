/*
 * Definizione delle funzioni relative alla gestione della ferrovia virtuale ed
 * ai sui componenti
 */
#ifndef VIRTUAL_H_

	#define VIRTUAL_H_

/* HEADER OBBLIGATORI*/

	#include"track.h"
	#include"train.h"

/* FUNZIONI PER I BINARI VIRTUALI */

	/* Restituisce un puntatore ad un binario virtuale allocato in memoria
	 * popolato col nome passato come parametro */
	TRACK* newVirtualTrack(char* pName);

	/* Dealloca la memoria relativa al binario virtuale e dei suoi componenti */
	void freeVirtualTrack(TRACK *pTrack);

/* FUNZIONI PER I TRENI VIRTUALI */

	/* Restituisce un puntatore ad un treno virtuale allocato in memoria
	 * popolato col nome passato come parametro */
	TRAIN* newVirtualTrain(char *pName);

	/* Dealloca la memoria relativa al treno virtuale e dei suoi componenti */
	void freeVirtualTrain(TRAIN *treno);

/* FUNZIONI PER LA FERROVIA VIRTUALE */

	/* Genera e collega fra di loro i binari virtuali, e li salva tutti in una
	 * lista */
	void newVirtualRailway();

	/* Dealloca la memoria relativa agli elementi ed ai sui componenti della
	 * lista di tutti i binari virtuali*/
	void freeVirtualRailway();

	/* Restituisce il puntatore al binario virtuale contenuto nella lista di
	 * tutti i binari virtuale corrispondente al nome passato come parametro,
	 * se non lo trova fallisce chiudendo l'esecuzione del programma */
	TRACK* searchInAVirtualRailway(char *pName);

#endif
