#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 123

// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
}

// creates or gets memory (create + get = cret)
// if successful returns ID of it otherwise return 0
int cret_shm() {
  int ID = shmget(KEY, 1024, IPC_CREAT | IPC_EXCL | 0644);
  if (ID != -1) {
    printf("creation of shm successful. ID: %d\n", ID);
    return ID;
  }
  else {
    printf("failed to create shared memory\n");
    print_error();
    return 0;
  }
}

// give a pointer to a pointer that will store the address of shmat
// attaches address to passed pointer
// if successful return 1, else return 0
int attach_shm(void **pt) {
  *pt = shmat(cret_shm(), 0, 0);
  if (*pt != -1) {
    printf("attaching shared memory successful\n");
    return 1;
  }
  else  {
    printf("failed to attach shared memory\n");
    print_error();
    return 0;
  }
}
// detaches shared memory at ID ID
// if successful return 1 otherwise return 0
int detach_shm(void **pt) {
  int r = shmdt(*pt); // gets address of shm
  if (r != -1) {
    printf("detach shared memory successful\n");
    return 1;
  }
  else {
    printf("failed to detach shared memory\n");
    print_error();
    return 0;
  }
}

// removes shared memory at ID ID. Only successful after all last process
// detaches from it
// if successful, return 1 otherwise return 0
int remove_shm() {
  int r = shmctl(cret_shm(), IPC_RMID, NULL);
  if (r != -1) {
    printf("removal of shared memory successful\n");
    return 1;
  }
  else {
    printf("failed to remove shared memory\n");
    print_error();
    return 0;
  }
}


// creates semaphore
// if successful returns its id otherwise return 0
int create_sem(int val) {
  printf("%d\n", val);
  int ID = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  // handling error
  if (ID != -1) {
    semctl(ID, 0, SETVAL, val);
    printf("Semaphore created: %d\n", ID);
    return ID;
  }
  else {
    printf("failed to create semaphore\n");
    print_error();
    return 0;
  }
}

//gets the shared memory id
// if successful return id, else return 0
int get_sem() {
  int sem_ID = semget(KEY, 0, 0644);
  if (sem_ID != -1) {
    return sem_ID;
  }
  else {
    printf("failed to get sem\n");
    print_error();
    return 0;
  }
}
// get sem value
// returns 1 if successful otherwise it returns 0
int get_sem_val() {
  int ID = get_sem();
  int sem_val = semctl(ID, 0, GETVAL);
  if (sem_val != -1) {
    printf("Semaphore value: %d\n", sem_val);
    return 1;
  }
  else {
    printf("failed to get sem value\n");
    print_error();
    return 0;
  }
}

//remove sem
// if successful return 1 otherwise return 0
int remove_sem() {
  int ID = get_sem();
  int r = semctl(ID, 0, IPC_RMID);
  if (r != -1) {
    printf("Semaphore removed\n");
    return 1;
  }
  else {
    printf("failed to remove semaphore\n");
    print_error();
    return 0;
  }
}


int main(int argc, char *argv[]) {
  int sem_ID;
  int shm_ID;
  char *par = argv[1];
  if (strcmp(par, "-c") == 0) {
    sem_ID = create_sem(atoi(argv[2]));
  }
  // case if v tag
  else if (strcmp(par, "-v") == 0) {
    // sem_ID = semget(KEY, 0, 0644);
    get_sem_val();
  }
  // case if r tag
  else if (strcmp(par, "-r") == 0) {
    // ID = = semget(KEY, 0, 0644);
    remove_sem();
  }
  else {
    printf("NOTHING HAPPENED\n");
  }
}
