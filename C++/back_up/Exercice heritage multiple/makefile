CC=g++
CFLAGS=-Wall
OBJ = test.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o test
