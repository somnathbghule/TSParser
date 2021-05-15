C=gcc
CFLAGS=-c -Wall 
#OBJ=objs/

all: tsParser

tsParser: main.o tp.o pat.o eit.o nit.o sdt.o descriptor.o
	$(C) main.o tp.o pat.o eit.o nit.o sdt.o descriptor.o -o tsParser

main.o: main.c
	$(C) $(CFLAGS) main.c

tp.o: tp.c
	$(C) $(CFLAGS) tp.c 

pat.o: pat.c
	$(C) $(CFLAGS) pat.c 

eit.o: eit.c
	$(C) $(CFLAGS) eit.c 

nit.o: nit.c
	$(C) $(CFLAGS) nit.c

sdt.o: sdt.c
	$(C) $(CFLAGS) sdt.c

descriptor.o: descriptor.c
	$(C) $(CFLAGS) descriptor.c 

clean:
	rm -rf *.o tsParser
