/*
 * Definizione delle funzioni relative alla gestione del sistema ETCS1
 */
#ifndef ETCS1_H_

	#define ETCS1_H_

/* HEADER OBBLIGATORI*/

	#include"train.h"

/* FUNZIONI DEL PROCESSO PADRE */

	/* Esegue la generazione della ferrovia e la funzione per effettuare i fork,
	 * il padre ritorna e gestisce l'attesa dei figli */
	void ETCS1();

	/* Esegue un processo figlio per ogni treno per eseguire il percorso di
	 * quest'ultimo, mentre il processo padre ritorna alla funzione chiamante */
	void forkETCS1();

/* FUNZIONI DEI PROCESSI FIGLI */

	/* Esegue iterativamente il percorso del treno passato come parametro */
	void loopETCS1(TRAIN *pTrain);

	/* Valuta il tipo di movimento o lo stallo che deve effettuare il treno
	 * passato come parametro, e restituisce zero se il suo percoro e` concluso
	 * altrimenti uno */
	int moveETCS1(TRAIN *pTrain);

/* FUNZIONI ACCESSORIE */

	/* Definizione segnale per sincronia fra i figli e il padre */
	void sigContinueETCS1(int signal);

#endif
