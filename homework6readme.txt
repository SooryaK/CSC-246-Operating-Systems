Soorya Kumar
CSC 246
7/18/17

Homework 6

Please use the make file I have submitted to compile.
I used my EOS account to remotely compile my files.
I have slightly modified the sleeper.c file to accept 
a parameter for the rider number and print the rider 
number in the print statement. Please use the sleeper.c
file that I have included in my submission.

Included in my submission are six files:
coordinator.c
coordinator.h
rider.c
rider.h
sleeper.c
sleeper.h

To compile and run (after all six files I have submitted are put in the same directory):

make
./coordinator <number of bumper cars> <number of riders> <length of simulation in seconds>

example:

make
./coordinator 8 12 20


Alternatively below are the compilation commands that are run when using the Make file I
have provided, they could be used in place of the make command:

gcc -g -Wall -std=gnu99 -lpthread   -c -o coordinator.o coordinator.c
gcc -g -Wall -std=gnu99 -lpthread   -c -o rider.o rider.c
gcc -g -Wall -std=gnu99 -lpthread   -c -o sleeper.o sleeper.c
gcc coordinator.o rider.o sleeper.o -o coordinator -lpthread
