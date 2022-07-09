CC=gcc
CFLAGS=-Wall -lncurses
OBJ = morpion.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
morpion: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o morpion
