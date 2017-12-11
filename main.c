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
#include "shm.h"
#include "sem.h"
#include "misc.h"
#define KEY 123
#define SHM_KEY 101


int main() {
  printf("Starting!!\n\n");

  //assumes shared memory and semaphore are already created
  down_sem(1);
  printf("Downed SEM\n");
  int *shm_pt = shmat(get_shm(), 0, 0);
  int size = *shm_pt;
  printf("%d\n", size);
  int fd = open("story", O_APPEND | O_RDWR );
  char buffer[10000];
  lseek(fd, -size, SEEK_END); //starts from end of file and work way back size bytes
  // printf("i seg fault \n");
  read(fd, buffer, size);
  printf("%s\n", buffer);
  char str[10000];
  fgets(str, 10000, stdin);
  str[strlen(str)-1] = '\n';
  write(fd, str, strlen(str));
  *shm_pt = strlen(str);
  shmdt(shm_pt);

  up_sem(1);
}
