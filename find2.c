/**
 This program uses threads to search for a
 word given any number of files, and displays
 the total word count for the given word among
 all files specified
 
 The compile command I used for this program:
 gcc -Wall -std=c99 find2.c -o find2 -lpthread
 I used my EOS account to remotely compile this program
 
 @file find.c
 @author Soorya Kumar
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

/** variable to track total word count across several threads and files*/
int totalWordCount = 0;

/** struct to hold two paramaters that will be passed to countWords method
    which are word (word to search for), and filename (file to search in), and
    it also stores the thread id for the thread that runs countWords*/
typedef struct threadArgs
{
    char word[100];
    char filename[100];
    pthread_t threadID;
} threadInfo;

/**
 This method counts the number of times a particular
 word appears in a particular file, and then adds that
 number to the global variable totalWordCount and
 then ends the thread
 
 It is run when a new thread is created
 
 @param cwThreadArgs a void pointer to the arguments for
 this method, which will be provided as a struct with the
 word to look for and the filename to search in
 */
void *countWords( void *cwThreadArgs ) 
{
    threadInfo *argsThread = (threadInfo *) cwThreadArgs; 
    int count = 0;
    char currentWord[100];
    FILE *inputFile = fopen( argsThread->filename, "r" );
    if ( !inputFile ) {
        fprintf( stderr, "File %s not found.\n", argsThread->filename );
        exit(100);
    }
    int count2 = 0;
    while ( fscanf( inputFile, "%s", currentWord) == 1 ) {
        if ( strcmp(argsThread->word, currentWord) == 0 ) {
            count++;
        }
        count2++;
    }
    totalWordCount += count;
    pthread_exit(NULL);
}

/**
 Finds out how many files need to be search
 creates a threadInfo struct for every thread to be created
 and populates with appropriate info and then creates all 
 threads needed. After all threads are completed, prints the 
 total word count of the word across all given files
 @param argc number of arguments
 @param argv array of command line arguments given
 */
int main( int argc, char *argv[] )
{
    char *word = argv[1];
    int files = argc - 2;
    static int argnumber = 2;
    threadInfo argsList[files];
    int terminatedThreads = 0;
    int counter = 0;
    while( counter < files) {
        strcpy(argsList[counter].word, word);
        strcpy(argsList[counter].filename, argv[argnumber]);
        pthread_create(&(argsList[counter].threadID), NULL, countWords, (void *) &argsList[counter]);
        counter++;
        argnumber++;
    }
    while (terminatedThreads < files) {
        pthread_join(argsList[terminatedThreads].threadID,NULL);
        terminatedThreads++;
    }
    printf("Total count for \"%s\": %d\n", word, totalWordCount);
}