/**
 CSC 246
 Homework 6
 @file sleeper.c
 @author Soorya Kumar
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sleeper.h"
void rideTime();
void walkAroundTime();

/* example of usage

int main( ) {
rideTime();
printf ("Ride over\n");
walkAroundTime();
printf ("Finished walking around  \n");
}
*/


void rideTime(int r) {

int seconds = ( random() % 5) + 1 ;
printf ("Rider %d is riding for %d seconds. \n", r, seconds);
sleep (seconds); 

}

void walkAroundTime(int r) {

int seconds = (random() % 10) + 1 ;
printf ("Rider %d is walking around the park for %d seconds.\n", r, seconds);
sleep (seconds);

}

