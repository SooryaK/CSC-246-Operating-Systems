/**
 This program uses process to search for a
 word given any number of files, and displays
 the total word count for the given word among
 all files specified
 
 The compile command I used for this program:
 gcc -Wall -std=c99 find.c -o find
 I used my EOS account to remotely compile this program
 
 @file find.c
 @author Soorya Kumar
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 This method counts the number of times a particular
 word appears in a particular file, and then adds
 returns that number to the parent process and terminates the 
 current child process
 
 This method is called by child process of the main parent process
 
 @param word the word to search for
 @param filename file to search in
 @param the argument number used to determine which file to search
 provided only to be able to return to main() if there is an error 
 */
void countWords(char* word, char* filename, int argnumber)
{
    int count = 0;
    char currentWord[100];
    FILE *inputFile = fopen( filename, "r" );
    if ( !inputFile ) {
        exit(100 + argnumber);
    }
    int count2 = 0;
    while ( fscanf( inputFile, "%s", currentWord) == 1 ) {
        if ( strcmp(word, currentWord) == 0 ) {
            count++;
        }
        count2++;
    }
    exit(count);
}

/**
 Finds out how many files need to be search
 creates a a new process for each file.
 There is one main parent that makes all the children.
 No child program makes further child processes.
 Each child process calls the countWords method to count the
 number of times the given word appears in that child process'
 assigned file. Each child process returns, when it terminates,
 the number of times the word is found in its file and a 
 cumulative sum is kept. After all child processes are complete
 the parent process prints the total word count of the word across
 all given files, or an error message if one of the files did not
 exist.
 @param argc number of arguments
 @param argv array of command line arguments given
 */
int main( int argc, char *argv[] )
{
    char* word = argv[1];
    int files = argc - 2;
    static int argnumber = 1;
    int id = -1;
    int exitValue = 0;
    int totalWordCount = 0;
    int terminatedChildren = 0;
    int counter = 0;
    while( id != 0 && counter < files) {
        id = fork();
        counter++;
        argnumber++;
    }
    if (id == 0) {
        countWords(word, argv[argnumber], argnumber);
    }
    else {
        bool err = false;
        char* errfile;
        while (terminatedChildren < files) {
            wait(&exitValue);
            if (WEXITSTATUS(exitValue) > 100) {
                errfile = argv[WEXITSTATUS(exitValue) - 100];
                err = true;
            }
            totalWordCount += WEXITSTATUS(exitValue);
            terminatedChildren++;
        }
        if (err == true) {
            fprintf( stderr, "File %s not found.\n", errfile );
            exit(100);
        }
        printf("Total count for \"%s\": %d\n", word, totalWordCount);
    }
}