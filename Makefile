CC=gcc
LD=ld
CFLAGS=-std=c99

SDIR=src
ODIR=obj
IMAGES=$(wildcard $(SDIR)/img/*.png)
IOBJS=$(IMAGES:$(SDIR)/img/%.png=$(ODIR)/%.o)

all: patch

patch: obj/main.o obj/dxa.o obj/exe.o $(IOBJS)
	$(CC) $(IOBJS) obj/dxa.o obj/exe.o obj/main.o -o patch $(CFLAGS)

obj/main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS) -o obj/main.o
	
obj/dxa.o: src/dxa.c
	$(CC) -c src/dxa.c $(CFLAGS) -o obj/dxa.o
	
obj/exe.o: src/exe.c src/btrav.inc
	$(CC) -c src/exe.c $(CFLAGS) -o obj/exe.o

$(IOBJS): $(ODIR)/%.o : $(SDIR)/img/%.png
	$(LD) -r -b binary $< -o $@
	
clean:
	rm obj/*.o