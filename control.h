#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 123

// prints error
void print_error();

// creates shared memory
// if successful returns ID of it otherwise return 0
int create_shm();

// gets id of shared memory
// if successful returns id, else return 0
int get_shm();

// give a pointer to a pointer that will store the address of shmat
// attaches address to passed pointer
// if successful return 1, else return 0
int attach_shm(int **pt);

// detaches shared memory at ID ID
// if successful return 1 otherwise return 0
int detach_shm(int **pt);

// removes shared memory at ID ID. Only successful after all last process
// detaches from it
// if successful, return 1 otherwise return 0
int remove_shm();

// creates semaphore
// if successful returns its id otherwise return 0
int create_sem(int val);

// get sem value
// returns 1 if successful otherwise it returns 0
int get_sem_val();

//gets the shared memory id
// if successful return id, else return 0
int get_sem();

// changes the val of the semaphore. returns the new value
int up_sem(int a);

// changes the val of the semaphore. returns the new value
int down_sem(int a);

// opens file story
// if successful return file descriptor else return -1
int open_file();

//gets the last line of the file and returns a string of it
char * story_last_line(int size);
