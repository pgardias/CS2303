# makefile -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)
#
# This makefile is used as follows to regenerate files for the qSim program:
#   make sim.o   --  Regenerates sim.o by compiling
#	make event.o  --  Regenerates event.o by compiling
#   make customer.o    --  Regenerates customer.o by compiling
#	make teller.o	-- Regenerates teller.o by compiling
#   make qSim      --  Regenerates the executable qSim file by compiling
#   make           --  Same as "make qSim"

CFLAGS =  -g -Wall

all: qSim docs

docs:
	doxygen
	
qSim: teller.o customer.o event.o sim.o eventqueue.o
	g++ $(CFLAGS) teller.o customer.o event.o sim.o eventqueue.o -o qSim

sim.o: sim.cpp sim.h teller.h event.h customer.h eventqueue.h
	g++ $(CFLAGS) -c sim.cpp

teller.o: teller.cpp teller.h event.h eventqueue.h
	g++ $(CFLAGS) -c teller.cpp

customer.o: customer.cpp customer.h teller.h eventqueue.h
	g++ $(CFLAGS) -c customer.cpp

event.o: event.cpp event.h
	g++ $(CFLAGS) -c event.cpp

eventqueue.o: eventqueue.cpp eventqueue.h event.h
	g++ $(CFLAGS) -c eventqueue.cpp

clean:
	rm -f *.o *.exe qSim