CC=gcc `pkg-config --cflags --libs gtk+-3.0` 
CFLAGS= `pkg-config --libs gtk+-3.0` -Wall -no-pie `pkg-config --libs gmodule-2.0`
OBJ = test.o 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o test
