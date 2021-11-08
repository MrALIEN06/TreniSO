/*
 * Definizione delle funzioni relative alla gestione dei file
 */
#ifndef FILE_H_

	#define FILE_H_

/* FUNZIONI PER L'APERTURA */

	/* Restituisce il descrittore del file creato nella posizione passata come
	 * parametro */
	int createFile(char *pFilePath);

	/* Restituisce il descrittore del file aperto nella posizione passata come
	 * parametro */
	int openFile(char *pFilePath);

/* FUNZIONI PER LA SCRITTURA */

	/* Scrive la stringa passata come parametro nel file corrispondente al
	 * descrittore anch'esso passato come parametro */
	void writeFile(int file,char *pString);

	/* Scrive il numero passato come parametro convertito in carattere
	 * all'inizio del file corrisopondente al descrittore, anch'esso passato
	 * come parametro */
	void writeIntFile(int file,int number);

	/* Scrive l'orario corrente sul file corripondente al descrittore passato
	 *  come parametro */
	void writeTime(int file);

/* FUNZIONI PER LA LETTURA */

	/* Restituisce il puntatore alla stringa allocata in memoria contenente il
	 * contenuto del file realtivo al descittore passato come parametro */
	char* readFile(int file);

	/* Restituisce il primo carattere convertito in intero del file
	 * corrisopondente al descrittore passato come parametro */
	int readIntFile(int file);

/* FUNZIONI PER LA CHIUSURA */

	/* Chiude il file associato al descrittore passato come parametro */
	void closeFile(int file);

#endif
