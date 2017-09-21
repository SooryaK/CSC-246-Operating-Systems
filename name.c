/**
 This program forks and has the child write 
 my last name and makes the parent wait for 
 the child to write my first name
 
 The compile command I used for this program:
 gcc -Wall -std=c99 name.c -o name
 I used my EOS account to remotely compile this program
 
 @file name.c
 @author Soorya Kumar
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/** Main Fuction */
int main() { 
    int id = 0;                    //initializes id variable and sets it to zero
    id = fork();                   //calls the fork system call and stores result in id variable
    if (id == 0) {                 //if id = 0 (if this is the child executing) this will be run
        printf("Kumar");           //print my last name if this is the child
    }
    else {                         //if id != 0 (if this is the parent executing) this will be run
        wait(NULL);                //make the parent wait for the child to finish executing
        printf(", Soorya\n");      //print my first name after waiting
    }
}