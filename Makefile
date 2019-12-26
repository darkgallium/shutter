CC=gcc
CFLAGS=-Wall -Wextra -O3 $(shell pkg-config --cflags gtk+-3.0)
LIBS=$(shell pkg-config --libs gtk+-3.0)

shutter: screenshot-area-selection.o shutter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

screenshot-area-selection.o: screenshot-area-selection.c screenshot-area-selection.h
	$(CC) $(CFLAGS) -o screenshot-area-selection.o -c screenshot-area-selection.c $(LIBS)

shutter.o: shutter.c screenshot-area-selection.h
	$(CC) $(CFLAGS) -o shutter.o -c shutter.c $(LIBS)
clean:
	rm -rf *.o shutter
