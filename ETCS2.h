/*
 * Definizione delle funzioni relative alla gestione del sistema ETCS2 come
 * client di RBC
 */
#ifndef ETCS2_H_

	#define ETCS2_H_

/* HEADER OBBLIGATORI*/

	#include"train.h"

/* FUNZIONI DEL PROCESSO PADRE */

	/* Esegue la generazione della ferrovia e la funzione per effettuare i fork,
	 * il padre ritorna e gestisce l'attesa dei figli */
	void ETCS2();

	/* Esegue la funzione per l'invio degli itinerari poi genera un processo
	 * figlio per ogni treno per eseguire il percorso di quest'ultimo, mentre il
	 *  processo padre ritorna alla funzione chiamante */
	void forkETCS2();

	/* Invia al server RBC l'itinerario del treno passato come parametro */
	void sendTrainItinerary(TRAIN *pTrain);

/* FUNZIONI DEI PROCESSI FIGLI */

	/* Esegue iterativamente le richieste per proseguire sul percorso del treno
	 * passato come parametro al server RBC*/
	void loopETCS2(TRAIN *pTrain);

	/* Valuta il tipo di movimento che deve effettuare il treno passato come
	 * parametro, e restituisce zero se il suo percoro e` concluso altrimenti
	 * uno */
	int moveETCS2(TRAIN *pTrain);

/* FUNZIONI ACCESSORIE */

	/* Definizione segnale per sincronia fra i figli e il padre */
	void sigContinueETCS2(int signal);

#endif
