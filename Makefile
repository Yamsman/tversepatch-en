CC=gcc
LD=ld
CFLAGS=-std=c99

SDIR=src
ODIR=obj
IMAGES=$(wildcard $(SDIR)/img/*.png)
IOBJS=$(IMAGES:$(SDIR)/img/%.png=$(ODIR)/%.o)

all: patch

patch: obj/main.o $(IOBJS)
	$(CC) obj/main.o $(IOBJS) -o patch $(CFLAGS)

obj/main.o:
	$(CC) -c src/main.c $(CFLAGS) -o obj/main.o

$(IOBJS): $(ODIR)/%.o : $(SDIR)/img/%.png
	$(LD) -r -b binary $< -o $@
	
clean:
	rm obj/*.o