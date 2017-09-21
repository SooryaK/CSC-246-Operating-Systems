/**
 CSC 246
 Homework 6
 @file coordinator.c
 @author Soorya Kumar
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "coordinator.h"
#include "rider.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t inLineForCar = PTHREAD_COND_INITIALIZER;

typedef struct
{
    int riderNumber;
    int carNumber;
    pthread_t threadID;
} riderInfo;

int totalNumberOfBumperCars;
int bumperCarsAvailable;
int nextCarIndex;
int returnCarIndex;
int numberOfRiders;
riderInfo * riderArray;
int * bumperCars;

int getInLine(int r){
    pthread_mutex_lock( &m1 );
    while (bumperCarsAvailable == 0)
    {
        pthread_cond_wait(&inLineForCar, &m1);
    }
    riderArray[r].carNumber = bumperCars[nextCarIndex];
    nextCarIndex = (nextCarIndex + 1) % totalNumberOfBumperCars;
    bumperCarsAvailable--;
    printf("Rider %d is now riding in car %d.\n", riderArray[r].riderNumber, riderArray[r].carNumber);
    pthread_mutex_unlock( &m1 );
    return riderArray[r].carNumber;
}

void returnCar(int r) {
    pthread_mutex_lock( &m1 );
    bumperCars[returnCarIndex] = riderArray[r].carNumber;
    returnCarIndex = (returnCarIndex + 1) % totalNumberOfBumperCars;
    bumperCarsAvailable++;
    printf("Rider %d returned car %d.\n", riderArray[r].riderNumber, riderArray[r].carNumber);
    riderArray[r].carNumber = 0;
    pthread_mutex_unlock( &m1 );
    pthread_cond_signal( &inLineForCar );

}

int main( int argc, char *argv[] )
{
    totalNumberOfBumperCars = atoi(argv[1]);
    bumperCarsAvailable = totalNumberOfBumperCars;
    numberOfRiders = atoi(argv[2]);
    int timeToSleep = atoi(argv[3]);
    bumperCars = (int *) malloc( totalNumberOfBumperCars * sizeof( int ) );
    for ( int i = 0; i < totalNumberOfBumperCars; i++ ){
        bumperCars[i] = i + 1;
    }
    riderArray = (riderInfo *) malloc( numberOfRiders * sizeof( riderInfo ) );
    for ( int i = 0; i < numberOfRiders; i++ ){
        riderArray[i].riderNumber = i + 1;
        riderArray[i].carNumber = 0;
    }    
    for ( int i = 0; i < numberOfRiders; i++ ){
        pthread_create(&(riderArray[i].threadID), NULL, startRider, (void *) &(riderArray[i].riderNumber));
    }
    sleep(timeToSleep);
    for ( int i = 0; i < numberOfRiders; i++ ){
        pthread_cancel(riderArray[i].threadID);
    }
    free(bumperCars);
    free(riderArray);
    exit( 0 );
}