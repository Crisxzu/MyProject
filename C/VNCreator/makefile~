CC=gcc
CFLAGS=-Wall -lncurses
OBJ = main.o menuControler.o menuView.o menuModel.o playVNControler.o playVNModel.o playVNView.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

vncreator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o vncreator
