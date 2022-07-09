CC=gcc
CFLAGS=-Wall -lncurses
OBJ = helw.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
helw: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o helw
