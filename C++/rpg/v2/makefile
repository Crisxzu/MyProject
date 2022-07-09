CC= g++
CFLAGS= -Wall
OBJ= main.o rpgclass.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

rpg: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm -f *.o rpg
