#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 123

// lazy handling of errors
void print_error() {
  if (strcmp(strerror(errno), "Success") != 0)
    printf("error: %s\n", strerror(errno));
}

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
    printf("Semaphore already exists\n");
    return 0;
  }
}

// get sem value
void get_sem_val(int ID) {
  int sem_val = semctl(ID, 0, GETVAL);
  printf("Semaphore value: %d\n", sem_val);
  print_error();
}

//remove sem
void remove_sem(int ID) {
  semctl(ID, 0, IPC_RMID);
  printf("Semaphore removed\n");
    print_error();
}

int main(int argc, char *argv[]) {
  int ID;
  printf("ID: %d\n", ID);
  char *par = argv[1];
  if (strcmp(par, "-c") == 0) {
    ID = create_sem(atoi(argv[2]));
    if (ID == 0) {
      printf("didn't create properly... exiting\n");
      return 0;
    }
  }
  // case if v tag
  else if (strcmp(par, "-v") == 0) {
    ID = = semget(KEY, 0, 0644);
    get_sem_val(ID);
  }
  // case if r tag
  else if (strcmp(par, "-r") == 0) {
    ID = = semget(KEY, 0, 0644);
    remove_sem(ID);
  }
  else {
    printf("NOTHING HAPPENED\n");
  }
}
