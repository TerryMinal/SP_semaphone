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
#include "sem.h"
#include "misc.h"

#define KEY 123
#define SHM_KEY 101

/* 
union semun {
  int val;    // Value for SETVAL 
  struct semid_ds *buf;    //Buffer for IPC_STAT, IPC_SET 
  unsigned short *array;  //Array for GETALL, SETALL 
  struct seminfo *__buf;  // Buffer for IPC_INFO
  (Linux-specific) 
};
*/

// creates semaphore
// if successful returns its id otherwise return 0
int create_sem() {
  int ID = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);

  if (ID != -1) {
    union semun sem;
    sem.val = 1;
    semctl(ID, 0, SETVAL, sem);
    printf("Semaphore created: %d\n", ID);
    printf("Value set: %d\n", sem.val);
    return ID;
  }
  else {
    printf("Failed to create semaphore\n");
    print_error();
    return 0;
  }
}

//gets the shared memory id
// if successful return id, else return 0
int get_sem() {
  int sem_ID = semget(KEY, 1, 0644);
  if (sem_ID != -1) {
    return sem_ID;
  }
  else {
    printf("Failed to get sem\n");
    print_error();
    return 0;
  }
}

// get sem value
// returns sem val if successful otherwise it returns 0
int get_sem_val() {
  int ID = get_sem();
  int sem_val = semctl(ID, 0, GETVAL);
  if (sem_val != -1) {
    return sem_val;
  }
  else {
    printf("Failed to get sem value\n");
    print_error();
    return 0;
  }
}

// changes the val of the semaphore. returns the new value
int up_sem(int a) {
  struct sembuf point;
  point.sem_num = 0;
  point.sem_flg = SEM_UNDO;
  point.sem_op = 1;
  int current = get_sem_val();
  int ID = get_sem();
  semop(ID, &point, 1);
  return current + a;
}

// changes the val of the semaphore. returns the new value
int down_sem(int a) {
  struct sembuf point;
  point.sem_num = 0;
  point.sem_flg = SEM_UNDO;
  point.sem_op = -1;
  int current = get_sem_val();
  int ID = get_sem();
  semop(ID, &point, 1);
  return current - a;
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
    printf("Failed to remove semaphore\n");
    print_error();
    return 0;
  }
}
