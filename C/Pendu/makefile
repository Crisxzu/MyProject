CC=gcc
CFLAGS=-Wall
OBJ = main.o penduControler.o penduModel.o penduView.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
pendu: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o pendu
