/*
 * Definizione delle funzioni relative alla gestione del server RBC
 */
#ifndef RBC_H_

	#define RBC_H_

/* HEADER OBBLIGATORI*/

	#include"trackList.h"
	#include"train.h"

	/* Esegue la generazione della ferrovia virtuale e le richieste dei treni
	 * attraverso un socket */
	void RBC();

	/* Restituisce un puntatore alla lista di binari virtuali relativi
	 * all'itinerario ricevuti dal socket corrispondente al descittore passato
	 * come parametro*/
	TRACKLIST* recivedTrainItinerary(int sock);

	/* Restituisce un valore corrispondente al fatto che il treno, passato come
	 * parametro, abbia finito o meno il suo itinerario, tale richiesta e`
	 * avviene tramite il socket del descrittore e scritto sul file relativo al
	 * descrittore, entrambi passati come parametri */
	int requestRBC(int sock,TRAIN *pTrain,int file);

	/* Valuta il movimento del treno passato come parametro e lo comunica
	 * attraverso il socket relativo al descrittore anch'esso passato come
	 * parametro */
	void moveRBC(int sock,TRAIN *pTrain);

	/* Scrive sul file di log passato come parametro la richiesta del treno e la
	 * sua accettazione entrambi passati come parametri*/
	void writeRBCLog(int file,TRAIN *pTrain,int state);

#endif
