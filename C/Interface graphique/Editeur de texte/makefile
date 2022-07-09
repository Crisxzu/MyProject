CC=gcc `pkg-config --cflags gtk+-3.0` 
CFLAGS=-Wall `pkg-config --libs gtk+-3.0`
OBJ = main.o callback.o error.o menu.o toolbar.o hotkey.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

editor: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o editor
