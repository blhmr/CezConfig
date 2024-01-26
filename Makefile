CC = gcc

CEZC = src/cezconfig.c
CEZH = include/cezconfig.h

main: $(CEZC) $(CEZH) main.c
	$(CC) -c main.c -o obj/main.o
	$(CC) -c $(CEZC) -o obj/cez.o
	$(CC) obj/* -o bin/main
