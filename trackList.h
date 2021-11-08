/*
 * Definizione della struttura e delle funzioni relative alla gestione degli
 * elementi di una lista di binari
 */
#ifndef TRACKLIST_H_

	#define TRACKLIST_H_

/* STRUTTURE DATI */

	/* Struttura dati per un elemento della lista di binari */
	typedef struct TRACKLIST {
		struct TRACK *item;
		struct TRACKLIST *next;
	} TRACKLIST;

/* HEADER OBBLIGATORI*/

	#include"track.h"

/* FUNZIONI PER LA GENERAZIONE*/

	/* Aggiunge il nuovo elemento binario passato come parametro alla lista
	 * passata anch'essa passata come parametro, allocandolo in memoria
	 * adeguatamente */
	void addTrackList(TRACKLIST *pTrackList, TRACK *pName);

	/* Resttiuisce un puntatore ad un elemento della lista allocato
	 * dinamicamente in memoria */
	TRACKLIST* storeTrackList();

	/* Restituisce un puntatore ad un elemento nullo della lista */
	TRACKLIST* getEmpityTrackList();

/* FUNZIONI PER LA PULIZIA */

	/* Dealloca la memoria relativa agli elementi della lista passata come
	 * parametro */
	void freeTrackList(TRACKLIST *pTrackList);

/* FUNZIONI ACCESSORIE */

	/* Restituisce il puntatore al binario contenuto nella lista passata come
	 * parametro corrispondente al nome passato come parametro, se non lo trova
	 * fallisce chiudendo l'esecuzione del programma */
	TRACK* searchTrackList(TRACKLIST *pTrackList, char *pName);

	/* Stampa a schermo i dati contenuti nei binari della lista passata come
	 * parametro */
	void statusTrackList(TRACKLIST *pTrackList);

	/* Stampa a schermo i nomi dei binari della lista passata come parametro */
	void showTrackList(TRACKLIST *pTrackList);

#endif
