CC = gcc
CFLAGS = -g -Wall -std=gnu99 -lpthread

coordinator: coordinator.o rider.o sleeper.o
	gcc coordinator.o rider.o sleeper.o -o coordinator -lpthread

coordinator.o: rider.h coordinator.h

sleeper.o: sleeper.h

rider.o: rider.h coordinator.h sleeper.h

clean:
	rm -f coordinator coordinator.o
	rm -f rider.o
	rm -f sleeper.o