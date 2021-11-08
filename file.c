#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>

#include"file.h"

//#define DEBUG

int createFile(char *pFilePath) {
	int file = open(pFilePath,O_RDWR|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);
	if(file==-1) {
		printf("\n[ERROR: createFile()] %s:%d -> Impossibile creare file\n",__FILE__,__LINE__);
		perror("[ERROR open()]");
		exit(EXIT_FAILURE);
	}
	if(chmod(pFilePath,S_IRWXU|S_IRWXG|S_IRWXO)) {	/*RIDONDANTE MA SCAVALCA LE POLITICHE DI SISTEMA*/
		printf("\n[ERROR: createFile()] %s:%d -> Impossibile modificare permessi file\n",__FILE__,__LINE__);
		perror("[ERROR chmod()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: createFile()]: %s:%d -> File:%s Descrittore:%d",__FILE__,__LINE__,pFilePath,file);
	#endif
	return file;
}

int openFile(char *pFilePath) {
	int file = open(pFilePath,O_RDONLY);
	if(file==-1) {
		printf("\n[ERROR: openFile()] %s:%d -> Impossibile aprire file\n",__FILE__,__LINE__);
		perror("[ERROR open()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: openFile()]: %s:%d -> File:%s Descrittore:%d",__FILE__,__LINE__,pFilePath,file);
	#endif
	return file;
}

void writeFile(int file,char *pString) {
	if(write(file,pString,strlen(pString))!=strlen(pString)) {
		printf("\n[ERROR: writeFile()] %s:%d -> Impossibile scrivere file\n",__FILE__,__LINE__);
		perror("[ERROR write()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: writeFile()]: %s:%d -> Scritto nel file %d",__FILE__,__LINE__,file);
	#endif
}

void writeIntFile(int file,int number) {
	if(lseek(file,0,SEEK_SET)==-1) {
		printf("\n[ERROR: writeIntFile()] %s:%d -> Impossibile scrivere intero su file\n",__FILE__,__LINE__);
		perror("[ERROR lseek()]");
		exit(EXIT_FAILURE);
	}
	char letter = (char)(number+48);
	if(write(file,&letter,1)!=1) {
		printf("\n[ERROR: writeIntFile()] %s:%d -> Impossibile scrivere intero su file\n",__FILE__,__LINE__);
		perror("[ERROR write()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: writeIntFile()]: %s:%d -> Scritto %d nel file %d",__FILE__,__LINE__,number, file);
	#endif
}

void writeTime(int file) {
	char *pString;
	time_t date,*pDate;
	pDate = &date;
	time(pDate);
	pString = asctime(localtime(pDate));
	writeFile(file,pString);
	#ifdef DEBUG
		printf("\n[Debug: writeTime()]: %s:%d -> Scritto orario nel file %d",__FILE__,__LINE__,file);
	#endif
}

char* readFile(int file){
	int fileLenght = lseek(file,0,SEEK_END);
	if(fileLenght==-1) {
		printf("\n[ERROR: readFile()] %s:%d -> Impossibile modificare offset file\n",__FILE__,__LINE__);
		perror("[ERROR lseek()]");
		exit(EXIT_FAILURE);
	}
	if(lseek(file,0,SEEK_SET)==-1) {
		printf("\n[ERROR: readFile()] %s:%d -> Impossibile modificare offset file\n",__FILE__,__LINE__);
		perror("[ERROR lseek()]");
		exit(EXIT_FAILURE);
	}
	char *pString = (char*)malloc(fileLenght);
	if(pString == NULL) {
		printf("\n[ERROR: readFile()] %s:%d -> Impossibile allocare memoria\n",__FILE__,__LINE__);
		perror("[ERROR malloc()]");
		exit(EXIT_FAILURE);
	}
	if(read(file,pString,fileLenght-1)==-1) {
		printf("\n[ERROR: readFile()] %s:%d -> Impossibile leggere file\n",__FILE__,__LINE__);
		perror("[ERROR read()]");
		exit(EXIT_FAILURE);
	}
	strtok(pString,"\n");
	#ifdef DEBUG
		printf("\n[Debug: readFile()]: %s:%d -> File:%d Contenuto:%s",__FILE__,__LINE__,file,pString);
	#endif
	return pString;
}

int readIntFile(int file) {
	if(lseek(file,0,SEEK_SET)==-1) {
		printf("\n[ERROR: readIntFile()] %s:%d -> Impossibile leggere intero da file\n",__FILE__,__LINE__);
		perror("[ERROR lseek()]");
		exit(EXIT_FAILURE);
	}
	char string[1];
	if(read(file,string,1)==-1) {
		printf("\n[ERROR: readIntFile()] %s:%d -> Impossibile leggere intero da file\n",__FILE__,__LINE__);
		perror("[ERROR read()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: readIntFile()]: %s:%d -> File:%d Contenuto:%c",__FILE__,__LINE__,file,string[0]);
	#endif
	return (int)(string[0]-48);
}

void closeFile(int file) {
	if(close(file)==-1) {
		printf("\n[ERROR: closeFile()] %s:%d -> Impossibile chiudere file\n",__FILE__,__LINE__);
		perror("[ERROR close()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: closeFile()]: %s:%d -> Chiuso file %d",__FILE__,__LINE__,file);
	#endif
}
