/**
 CSC 246
 Homework 6
 @file rider.c
 @author Soorya Kumar
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "coordinator.h"
#include "rider.h"
#include "sleeper.h"

void * startRider(void * riderNumber) {
    int * r = (int *) riderNumber;
    int oldstate;
    int oldtype;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);
    while(true) {
        walkAroundTime(*r);
        getInLine(*r);
        rideTime(*r);
        returnCar(*r);
    }
}