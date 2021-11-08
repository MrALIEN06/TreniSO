/*
 * Definizione delle funzioni relative alla gestione della ferrovia
 */
#ifndef RAILWAY_H_

	#define RAILWAY_H_

/* HEADER OBBLIGATORI*/

	#include"track.h"

/* FUNZIONI PER LA GENERAZIONE*/

	/* Genera e collega fra di loro i binari, e li salva tutti in una lista */
	void newRailway();

/* FUNZIONI PER LA PULIZIA */

	/* Dealloca la memoria relativa agli elementi ed ai sui componenti della
	 * lista di tutti i binari */
	void freeRailway();

/* FUNZIONI ACCESSORIE */

	/* Restituisce il puntatore al binario contenuto nella lista di tutti i
	 * binari corrispondente al nome passato come parametro, se non lo trova
	 * fallisce chiudendo l'esecuzione del programma */
	TRACK* searchInARailway(char *pName);

#endif
