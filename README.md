# CSC-246-Operating-Systems
Programming Assignments from CSC 246 Operating Systems

This repository includes Programming Assignments from my CSC246 Operating Systems Class

name.c This is a simple program that implements the use of a fork() command to show how a single program can be used to create multiple process and make those process diverge and perform different tasks.

find.c This is a more advanced program that how to use fork() and mutiple processes to count the number of times a particular word (specified by user input) appears across several given input text files.

find2.c This program accomplishes the same thing as find.c but uses threads (pthreads specifically) instead of processes to provide the same the result.

Life.c This program simulates Conway's Game of Life. It accomplishes this by creating a thread for every cell in the simulation that individually calculates how that cell should be updated/if it should be updated for the next updated iteration of the simulation. This program also uses other important C concepts such as using structs to pass multiple parameters to a new thread, dynamic memory allocations, pointers and struct pointers.

barrier.cpp This program demonstrates process/thread synchronization. It creates several threads and uses a mutex (mutual exclusion semaphore) as well as a semaphore to make all the threads execute to a certain point where they must all wait until all the threads reach that point in the code (essentially creating a barrier for the threads). Once all the threads have reached the barrier, the barrier is let down (the semaphore is signaled to let the threads proceed) to finish execution.

coordinator.c, coordinator.h, rider.c, rider.h, sleeper.c, sleeper.h These files together create a simulation in which rider "objects" (each represented by a new thread) go to a fair where they can walk around for a random amount of time, and then ride bumper cars. There is a limited amount of bumper cars and a bumper car cannot be used while it is in use by another rider. While all the bumper cars a taken, a queue is formed for the remaining waiting riders. The simulation continues for a user input given amount of time. All of this is controlled using mutexes and semaphores to manage the riders and when they can access or give up bumper cars. It also demonstrates how to start a thread, whose initial function is in a different file. A makefile and readme (homework6readme.txt) is also provided.
