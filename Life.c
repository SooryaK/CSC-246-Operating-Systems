/**
 This program simulatest the game of life 
 using threads
 
 The compile command I used for this program:
 gcc -Wall -std=c99 Life.c -o Life -lpthread
 
 And the command to run:
 ./Life <filename> <integer>
 example: ./Life StableState.txt 3
 
 I used my EOS account to remotely compile this program
 
 @file Life.c
 @author Soorya Kumar
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

/** struct to hold two paramaters that will be passed to updateCell method
    which are word row and column coordinates the thread will use. It also
    store the thread id for the thread */
typedef struct threadArgs
{
    int threadRow;
    int threadColumn;
    pthread_t threadID;
} threadData;

/** variable of grid before generation update*/
int** beforeGrid;

/** variable of grid after generation update*/
int** afterGrid;

/** rows used in grid */
int rows;

/** columns used in grid */
int columns;

/** Method to calculate the value of one cell for the next generation
    Calculates the value by conditionally adding sum of neighboring cells
    (not adding neighbors if they do not exist/are not valid grid spaces)
    then if space is a 0 in old board, can only change to a 1 if sum of neighbors is 3
    if space is 1 in old board, can only stay a 1 if sum is 2 or 3
    Runs when a thread is created
    
    @param threadParam the parameters passed into the function, should 
    be passed in as a threadData struct
 */
void *updateCell( void *threadParam )
{
    threadData * param = (threadData * ) threadParam;
    int sum = 0;
    if ( param->threadRow > 0 ) {
        sum += beforeGrid[(param->threadRow) - 1][param->threadColumn];
    }
    if ( param->threadColumn > 0 ) {
        sum += beforeGrid[param->threadRow][(param->threadColumn) - 1];
    }
    if ( param->threadRow < rows - 1 ) {
        sum += beforeGrid[(param->threadRow) + 1][param->threadColumn];
    }
    if ( param->threadColumn < columns - 1 ) {
        sum += beforeGrid[param->threadRow][(param->threadColumn) + 1];
    }
    if ( param->threadRow > 0 && param->threadColumn > 0 ) {
        sum += beforeGrid[(param->threadRow) - 1][(param->threadColumn) - 1];
    }
    if ( param->threadRow > 0 && param->threadColumn < columns - 1 ) {
        sum += beforeGrid[(param->threadRow) - 1][(param->threadColumn) + 1];
    }
    if ( param->threadRow < rows - 1 && param->threadColumn > 0 ) {
        sum += beforeGrid[(param->threadRow) + 1][(param->threadColumn) - 1];
    }
    if ( param->threadRow < rows - 1 && param->threadColumn < columns - 1 ) {
        sum += beforeGrid[(param->threadRow) + 1][(param->threadColumn) + 1];
    }
    if ( beforeGrid[param->threadRow][param->threadColumn] == 0 ) {
        if ( sum == 3 ) {
            afterGrid[param->threadRow][param->threadColumn] = 1;
        }
        else {
            afterGrid[param->threadRow][param->threadColumn] = 0;
        }
    }
    else if ( beforeGrid[param->threadRow][param->threadColumn] == 1 ) {
        if ( sum == 3 || sum == 2 ) {
            afterGrid[param->threadRow][param->threadColumn] = 1;
        }
        else {
            afterGrid[param->threadRow][param->threadColumn] = 0;
        }
    }
    pthread_exit(NULL);
}

/** 
Gets filename and number of generations from command line arguments
Opens file and initializes grid from file
Operates in a larger loop for the number of generations to create threads
to update every single cell in the grid, then joins all the threads, prints
the new grid, and sets the old grid equal to the new grid 
*/
int main( int argc, char *argv[] )
{
    char *filename = argv[1];
    int generations = atoi(argv[2]);
    FILE *inputFile = fopen( filename, "r" );
    if ( !inputFile ) {
        fprintf( stderr, "File %s not found.\n", filename );
        exit(100);
    }
    if (fscanf( inputFile, "%d%d", &rows, &columns) != 2) {
        fprintf( stderr, "Improper input. Rows and columns not formatted correctly\n" );
        exit(100);
    }
    beforeGrid = (int **) malloc( rows * sizeof( int* ) );
    afterGrid = (int ** ) malloc( rows * sizeof( int* ) );
    for ( int i = 0; i < rows; i++ ){
        beforeGrid[i] = (int *) malloc( columns * sizeof( int ) );
        afterGrid[i] = (int *) malloc( columns * sizeof( int ) );
    }
    for ( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < columns; j++ ) {
            fscanf( inputFile, "%d", &(beforeGrid[i][j]) );
            if ( j == columns - 1) {
                printf("%d", beforeGrid[i][j]);
            }
            else {
                printf("%d ", beforeGrid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    threadData threadArray[rows][columns];
    while ( generations > 0 ) {
        for ( int i = 0; i < rows; i++ ){
            for ( int j = 0; j < columns; j++ ) {
                threadArray[i][j].threadRow = i;
                threadArray[i][j].threadColumn = j;
                pthread_create(&(threadArray[i][j].threadID), NULL, updateCell, (void *) &threadArray[i][j]);
            }
        }
        for ( int i = 0; i < rows; i++ ) {
            for ( int j = 0; j < columns; j++ ) {
                pthread_join(threadArray[i][j].threadID,NULL);
            }
        }
        for ( int i = 0; i < rows; i++ ) {
            for ( int j = 0; j < columns; j++ ) {
                if ( j == columns - 1) {
                    printf("%d", afterGrid[i][j]);
                    beforeGrid[i][j] = afterGrid[i][j];
                }
                else {
                    printf("%d ", afterGrid[i][j]);
                    beforeGrid[i][j] = afterGrid[i][j];
                }
            }
            printf("\n");
        }
        printf("\n");
        generations--;
    }
    for ( int i = 0; i < rows; i++ ){
        free(beforeGrid[i]);
        free(afterGrid[i]);
    }
    free(beforeGrid);
    free(afterGrid);
}