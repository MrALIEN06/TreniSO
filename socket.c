#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/socket.h>
#include<sys/un.h>

#include"socket.h"

//#define DEBUG

#define SOCK_PATH "SocketTrain"
#define MAX_LISTEN 10
#define DIM_SOCK 10

struct sockaddr_un sockAddr;
struct sockaddr *pSockAddr = (struct sockaddr*)&sockAddr;
int addrLengh;
socklen_t* pAddrLengh;

void populateAddress() {
	sockAddr.sun_family = AF_UNIX;
	strcpy(sockAddr.sun_path,SOCK_PATH);
	addrLengh = sizeof(sockAddr);
	pAddrLengh = (socklen_t*)&addrLengh;
	#ifdef DEBUG
		printf("\n[Debug: populateAddress()]: %s:%d -> Indirizzo socket impostato",__FILE__,__LINE__);
	#endif
}

int openSocket() {
	int sock = socket(PF_UNIX,SOCK_STREAM,0);
	if(sock==-1) {
		printf("\n[ERROR: openSocket()] %s:%d -> Impossibile generare socket\n",__FILE__,__LINE__);
		perror("[ERROR socket()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: openSocket()]: %s:%d -> Apertura soket %d",__FILE__,__LINE__,sock);
	#endif
	return sock;
}

int openServer() {
	populateAddress();
	int sock = openSocket();
	unlink(sockAddr.sun_path);
	if(bind(sock,pSockAddr,addrLengh)==-1) {
		printf("\n[ERROR: openServer()] %s:%d -> Impossibile assegnare l'indirizzo al socket\n",__FILE__,__LINE__);
		perror("[ERROR bind()]");
		exit(EXIT_FAILURE);
	}
	if(listen(sock,MAX_LISTEN)==-1) {
		printf("\n[ERROR: openServer()] %s:%d -> Impossibile impostare lista d'attesa\n",__FILE__,__LINE__);
		perror("[ERROR listen()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: openServer()]: %s:%d -> Impostato socket lato server %d",__FILE__,__LINE__,sock);
	#endif
	return sock;
}

int acceptConnect(int sock) {
	#ifdef DEBUG
		printf("\n[Debug: acceptConnect()]: %s:%d -> Server in attesa sul socket %d",__FILE__,__LINE__,sock);
	#endif
	int tmpSock=accept(sock,pSockAddr,pAddrLengh);
	if(tmpSock==-1) {
		printf("\n[ERROR: acceptConnect] %s:%d -> Impossibile accettare connessione\n",__FILE__,__LINE__);
		perror("[ERROR accept()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: acceptConnect()]: %s:%d -> Richiesta accettata e trasferita sul socket %d",__FILE__,__LINE__,tmpSock);
	#endif
	return tmpSock;
}

int openClient() {
	static int flag=0;
	if(flag==0) {
		populateAddress();
		flag++;
	}
	int sock = openSocket();
	#ifdef DEBUG
		printf("\n[Debug: openClient()]: %s:%d -> Impostato socket lato client %d",__FILE__,__LINE__,sock);
	#endif
	return sock;
}

void requestConnect(int sock) {
	#ifdef DEBUG
		printf("\n[Debug: connectServer()]: %s:%d -> Invio richiesta sul socket %d",__FILE__,__LINE__,sock);
	#endif
	if(connect(sock,pSockAddr,addrLengh)==-1) {
		printf("\n[ERROR: connectServer()] %s:%d -> Impossibile stabilire connessione\n",__FILE__,__LINE__);
		perror("[ERROR connect()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: connectServer()]: %s:%d -> Richiesta accettata sul socket %d",__FILE__,__LINE__,sock);
	#endif
}

void writeSocket(int sock, char *pString) {
	if(write(sock,pString,strlen(pString))!=strlen(pString)) {
		printf("\n[ERROR: writeSocket()] %s:%d -> Impossibile scrivere sul socket\n",__FILE__,__LINE__);
		perror("[ERROR write()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: writeSocket()]: %s:%d -> Scritto %s nel socket %d",__FILE__,__LINE__,pString, sock);
	#endif
}

void writeIntSocket(int sock, int number) {
	char letter = (char)(number+48);
	if(write(sock,&letter,1)!=1) {
		printf("\n[ERROR: writeIntSocket()] %s:%d -> Impossibile scrivere intero sul socket\n",__FILE__,__LINE__);
		perror("[ERROR write()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: writeIntSocket()]: %s:%d -> Scritto %d nel socket %d",__FILE__,__LINE__,number,sock);
	#endif
}

char* readSocket(int sock) {
	char *pString = (char*)calloc(DIM_SOCK+1,sizeof(char));
	if(pString == NULL) {
		printf("\n[ERROR: readSocket()] %s:%d -> Impossibile allocare memoria\n",__FILE__,__LINE__);
		perror("[ERROR malloc()]");
		exit(EXIT_FAILURE);
	}
	if(read(sock,pString,DIM_SOCK)==-1) {
		printf("\n[ERROR: readSocket()] %s:%d -> Impossibile leggere socket\n",__FILE__,__LINE__);
		perror("[ERROR read()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: readSocket()]: %s:%d -> Socket: %d Contenuto: %s",__FILE__,__LINE__,sock,pString);
	#endif
	return pString;
}

int readIntSocket(int sock) {
	char string[1];
	if(read(sock,string,1)==-1) {
		printf("\n[ERROR: readIntSocket()] %s:%d -> Impossibile leggere intero dal socket\n",__FILE__,__LINE__);
		perror("[ERROR read()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: readIntSocket()]: %s:%d -> Socket: %d Contenuto: %c",__FILE__,__LINE__,sock,string[0]);
	#endif
	return (int)(string[0]-48);
}

void closeSocket(int sock) {
	if(close(sock)==-1) {
		printf("\n[ERROR: closeSocket()] %s:%d -> Impossibile chiudere socket\n",__FILE__,__LINE__);
		perror("[ERROR close()]");
		exit(EXIT_FAILURE);
	}
	#ifdef DEBUG
		printf("\n[Debug: closeSocket()]: %s:%d -> Chiusura del socket",__FILE__,__LINE__);
	#endif
}
