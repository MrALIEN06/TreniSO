#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include"ETCS1.h"
#include"ETCS2.h"
#include"RBC.h"

//#define DEBUG

int main(int argc, char *argv[]) {
	#ifdef DEBUG
		printf("\n\tFile:\t\t%s\n\tData:\t\t%s\n\tOra:\t\t%s\n\tCompilatore:\t",__FILE__,__DATE__,__TIME__);
		if(__STDC__) {printf("ANSI C\n");}
		else {printf("NOT ANSI C\n");}
	#endif
	if((argc==2)&&(!strcmp(argv[1],"ETCS1\0"))) {ETCS1();}
	if((argc==2)&&(!strcmp(argv[1],"ETCS2\0"))) {ETCS2();}
	if((argc==3)&&(!strcmp(argv[1],"ETCS2\0"))&&(!strcmp(argv[2],"RBC\0"))) {RBC();}
	#ifdef DEBUG
		printf("\n[Debug: main()]: %s:%d -> Esecuzione programma terminata\n",__FILE__,__LINE__);
	#endif
	return EXIT_SUCCESS;
}
