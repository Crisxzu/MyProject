CC=gcc
CFLAGS=-Wall -lncurses
OBJ = grille.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
grille: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o grille
