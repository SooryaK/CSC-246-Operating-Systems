/**
 the command I used to compile this program
 g++ -Wall -std=c++0x barrier.cpp -o barrier -lpthread
 
 the command I used to run this program:
 ./barrier
 
 @author Soorya Kumar
*/
#include <pthread.h>
#include <iostream>
using namespace std;


pthread_mutex_t mutex   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
int totalThreads = 0;
char taskWhileWaiting = 'A';

void waitForOthers();

void * Restaurant(void * param);


int main(){

    pthread_t hungryThd[4]; 
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 
   
    // create threads
    for ( int i = 0; i < 4; i++ ) {
        pthread_mutex_lock( &mutex );
        totalThreads++;
        pthread_create(&(hungryThd[i]), &attr, Restaurant, NULL);
        
    }
   
    // join threads
    for ( int i = 0; i < 4; i++ ) {
        pthread_join(hungryThd[i], NULL);
    }
    return 0;
}

void waitForOthers(){
    // add barrier and output code here
    int threadNumber = totalThreads;
    
    if ( totalThreads < 4 ) {
        cout << "I am thread " << threadNumber << ", working on Task " << taskWhileWaiting++ << ", and waiting to eat." << endl;
        pthread_cond_wait( &notFull, &mutex );
    }
    else {
        cout << "I am thread " << threadNumber << ", working on Task " << taskWhileWaiting << ", and waiting to eat." << endl;
        //pthread_cond_broadcast( &notFull ); //this works too (in place of the for loop below)
        for (int i = 0; i < 3; i++) {
            pthread_cond_signal( &notFull );
        }
    }
    pthread_mutex_unlock( &mutex );
    cout << "I am thread " << threadNumber << " and I am eating." << endl;
}


void * Restaurant(void * param){

    // call wait function
    
    waitForOthers();
    pthread_exit(NULL);
   
}