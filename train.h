/*
 * Definizione della struttura e delle funzioni relative alla gestione dei treni
 */
#ifndef TRAIN_H_

	#define TRAIN_H_

/* HEADER OBBLIGATORI*/

	#include "track.h"
	#include "trackList.h"

/* STRUTTURE DATI */

	/* Struttura dati per i treni */
	typedef struct TRAIN {
		char *name;
		int log;
		TRACK *position;
		TRACKLIST *itinerary;
		TRACKLIST *path;
	} TRAIN;

/* FUNZIONI PER LA GENERAZIONE*/

	/* Restituisce un puntatore ad un treno allocato in memoria popolato col
	 * nome passato come parametro, dal descrittore del file di log associato al
	 * treno creato appositamente e dalla lista di binari relativi
	 * all'itinerario letti dal file corrispondente*/
	TRAIN* newTrain(char *pName);

	/* Resttiuisce un puntatore ad un treno allocato dinamicamente in memoria */
	TRAIN* storeTrain();

/* FUNZIONI PER IL MOVIMENTO*/

	/* Imposta il treno passato come parametro sul primo binario della lista e
	 * lo scrivere sul file di log */
	void startTrain(TRAIN *pTrain);

	/* Imposta il treno passato come parametro sul successivo binario della
	 * lista e lo scrivere sul file di log */
	void moveTrain(TRAIN *pTrain);

	/* Imposta il treno passato come parametro sull'ultimo binario della lista e
	 * lo scrivere sul file di log */
	void stopTrain(TRAIN *pTrain);

	/* Scrive sul file di log che il treno passato come parametro e` rimasto
	 * fermo */
	void lockTrain(TRAIN *pTrain);

/* FUNZIONI PER LA PULIZIA */

	/* Dealloca la memoria relativa al treno e dei suoi componenti, inoltre
	 * chiude il file di log ad esso associato */
	void freeTrain(TRAIN *pTrain);

/* FUNZIONI ACCESSORIE */

	/* Restituisce un puntatore alla lista di binari relativi all'itinerario
	 * letti e convertiti dal file nella posizione passata come parametro*/
	TRACKLIST* getTrainItinerary(char *pPathFile);

	/* Scrive sul file di log relativo al treno passato come parametro */
	void writeTrainLog(TRAIN *pTrain);

	/* Stampa a schermo i dati del treno passato come parametro */
	void statusTrain(TRAIN *pTrain);

#endif
