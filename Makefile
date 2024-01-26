CC = gcc

CEZC = src/cezconfig.c
CEZH = include/cezconfig.h

install: $(CEZC) $(CEZH)
	sudo cp $(CEZH) /usr/include/
	gcc -c $(CEZC) -o cez.o
	ar rcs libcezconfig.a cez.o
	rm cez.o
	sudo mv libcezconfig.a /usr/lib/

uninstall:
	sudo rm /usr/include/cezconfig.h
	sudo rm /usr/lib/libcezconfig.a
