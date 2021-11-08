/*
 * Definizione della struttura e delle funzioni relative alla gestione dei binari
 */
#ifndef TRACK_H_

	#define TRACK_H_

/* STRUTTURE DATI */

	/* Struttura dati per i binari */
	typedef struct TRACK {
		char *name;
		int file;
		struct TRACKLIST *near;
	} TRACK;

/* HEADER OBBLIGATORI*/

	#include"trackList.h"

/* FUNZIONI PER LA GENERAZIONE*/

	/* Restituisce un puntatore ad un binario allocato in memoria popolato col
	 * nome passato come parametro e dal descrittore del file associato al
	 * binario creato appositamente */
	TRACK* newTrack(char* pName);

	/* Resttiuisce un puntatore ad un binario allocato dinamicamente in memoria */
	TRACK* storeTrack();

	/* Collega i due binari pasati come parametri attraverso il campo vicini */
	void linkTrack(TRACK* pTrack1, TRACK* pTrack2);

/* FUNZIONI PER LA PULIZIA */

	/* Dealloca la memoria relativa al binario e dei suoi componenti, inoltre
	 * chiude il file ad esso associato */
	void freeTrack(TRACK *pTrack);

/* FUNZIONI ACCESSORIE */

	/* Stampa a schermo i dati del binario passato come parametro */
	void statusTrack(TRACK *pTrak);

#endif
