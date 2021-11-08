/*
 * Definizione delle funzioni relative alla gestione dei socket
 */
#ifndef SOCKET_H_

	#define SOCKET_H_

/* FUNZIONI PER LA GENERAZIONE*/

	/* Imposta i parametri dell'indirizzo del socket */
	void populateAddress();

	/* Restituisce il descrittore di un nuovo socket */
	int openSocket();

/* FUNZIONI LATO SERVER */

	/* Restituisce il descrittore del socket impostato dal lato server */
	int openServer();

	/* Restituisce un descrittore ad un socket temporaneo relativo ad una
	 * connessione accettata sul descrittore del socket passato come parametro*/
	int acceptConnect(int sock);

/* FUNZIONI LATO CLIENT */

	/* Restituisce il descrittore del socket impostato dal lato client */
	int openClient();

	/* Invia una richiesta di connessione al socket relativo al descrittore
	 * passato come parametro */
	void requestConnect(int sock);

/* FUNZIONI PER LA SCRITTURA */

	/* Scrive la stringa passata come parametro nel socket corrispondente al
	 * descrittore anch'esso passato come parametro */
	void writeSocket(int sock, char *pString);

	/* Scrive il numero passato come parametro convertito in carattere nel
	 * socket corrisopondente al descrittore, anch'esso passato come parametro */
	void writeIntSocket(int sock, int number);

/* FUNZIONI PER LA LETTURA */

	/* Restituisce il puntatore alla stringa allocata in memoria contenente il
	 * contenuto del socket realtivo al descittore passato come parametro */
	char* readSocket(int sock);

	/* Restituisce il carattere convertito in intero contenuto nel socket
	 * corrisopondente al descrittore passato come parametro */
	int readIntSocket(int sock);

/* FUNZIONI PER LA CHIUSURA */

	/* Chiude la connessione sul socket relativo al descrittore passato come
	 * parametro */
	void closeSocket(int sock);

#endif
