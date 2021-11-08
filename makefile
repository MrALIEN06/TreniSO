SHELL = /bin/sh

CC = gcc

#DEBUG =-DDEBUG -g
CFLAG = $(DEBUG) -Wall

PROJECT =Treni

OBJECTS = file.o socket.o trackList.o track.o railway.o train.o virtual.o RBC.o ETCS2.o ETCS1.o main.o

SEPARETOR1 = ------------------------------------------------------------
SEPARETOR2 = ============================================================

all:$(PROJECT)

$(PROJECT):$(OBJECTS)
	@ echo "$(SEPARETOR2)$(SEPARETOR2)"
	$(CC) $(CFLAG) -o $@ $^
	@ echo "$(SEPARETOR2)$(SEPARETOR2)"

main.o: main.c ETCS1.o ETCS2.o RBC.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

ETCS1.o: ETCS1.c railway.o trackList.o file.o train.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

ETCS2.o: ETCS2.c railway.o trackList.o socket.o train.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

RBC.o: RBC.c virtual.o socket.o file.o trackList.o train.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

virtual.o: virtual.c track.o train.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

train.o: train.c railway.o file.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

railway.o: railway.c trackList.o track.o train.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

track.o: track.c file.o trackList.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

trackList.o: trackList.c file.o track.o
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

socket.o: socket.c
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

file.o: file.c
	@ echo "Target: $@\n$(SEPARETOR1)"
	$(CC) $(CFLAG) -c -o $@ $<
	@ echo "$(SEPARETOR1)\n"

.PHONY: clean setup

clean:
	@ echo "Clean binary file:\n$(SEPARETOR2)"
	- rm ./*.o
	@ echo "$(SEPARETOR2)\n"

setup:
	@ echo "Generate file folder:\n$(SEPARETOR2)"
	mkdir ./file
	mkdir ./file/binari
	mkdir ./file/itinerari
	mkdir ./file/log
	unzip ./Tracciati.zip -d ./file/itinerari/
	@ echo "$(SEPARETOR2)\n"
