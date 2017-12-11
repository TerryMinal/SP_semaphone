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
#include "control.h"
#include "shm.h"
#include "misc.h"
#define KEY 123

// creates or gets memory
// if successful returns ID of it otherwise return 0
int create_shm() {
  int ID = shmget(KEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
  if (ID != -1) {
    printf("Sucessfully created shared memory. ID: %d\n", ID);
    return ID;
  }
  else {
    printf("Failed to create shared memory\n");
    print_error();
    return -1;
  }
}

// gets id of shared memory
// if successful returns id, else return 0
int get_shm() {
  int ID = shmget(KEY, sizeof(int), 0);
  if (ID != -1) {
    //printf("Get of shm successful. ID: %d\n", ID);
    return ID;
  }
  else {
    printf("Failed to get shared memory\n");
    //print_error();
    return -1;
  }
}
// give a pointer to a pointer that will store the address of shmat
// attaches address to passed pointer
// if successful return 1, else return 0
// int attach_shm(int **pt) {
//   *pt = shmat(get_shm(), 0, 0);
//   if ( *pt !=  -1) {
//     printf("attaching shared memory successful\n");
//     return 1;
//   }
//   else  {
//     printf("failed to attach shared memory\n");
//     print_error();
//     return 0;
//   }
// }

// detaches shared memory at ID ID
// if successful return 1 otherwise return 0
// int detach_shm(int **pt) {
//   int r = shmdt(*pt); // gets address of shm
//   if (r != -1) {
//     printf("detach shared memory successful\n");
//     return 1;
//   }
//   else {
//     printf("failed to detach shared memory\n");
//     print_error();
//     return 0;
//   }
// }


// removes shared memory at ID ID. Only successful after all last process
// detaches from it
// if successful, return 1 otherwise return 0
int remove_shm() {
  int ID = get_shm();
  int r = shmctl(ID, IPC_RMID, NULL);
  if (r != -1) {
    printf("Successfully removed shared memory. ID: %d\n", ID);
    return 1;
  }
  else {
    printf("Failed to remove shared memory\n");
    print_error();
    return -1;
  }
}
