CFLAGS =  -g -Wall

all: PA5 docs

docs:
	doxygen
	
PA5: Doodlebug.o Ant.o Organism.o main.o
	g++ $(CFLAGS) Doodlebug.o Ant.o Organism.o main.o -o PA5
	
main.o: main.cpp main.h Organism.h Ant.h Doodlebug.h
	g++ $(CFLAGS) -c main.cpp 
	
Doodlebug.o: Doodlebug.cpp Organism.h main.h Doodlebug.h
	g++ $(CFLAGS) -c Doodlebug.cpp
	
Ant.o: Ant.cpp Organism.h main.h Ant.h
	g++ $(CFLAGS) -c Ant.cpp
	
Organism.o: Organism.cpp Organism.h main.h
	g++ $(CFLAGS) -c Organism.cpp

clean:
	rm -f *.o *.exe PA5