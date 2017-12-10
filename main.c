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

//gets the last line of the file and returns a string of it
char * story_last_line(int size) {
  int fd = open("story", O_APPEND | O_RDWR);
  char *buffer;
  lseek(fd, -size, SEEK_END); //starts from end of file and work way back size bytes
  read(fd, buffer, size);
  return buffer;
}

int main() {
  printf("semaphore val: %d\n", get_sem_val());
  //assumes shared memory and semaphore are already created
  if (get_sem_val() <= 0) {
    printf("file current in use\n");
    while(get_sem_val() <= 0) { /* blocking */ };
  }
  else {
    down_sem(1);
    int *shm_pt;
    shm_pt = shmat(get_shm(), sizeof(int), 0);
    int size = *shm_pt;
    printf("size: %d\n", size);
    printf("story below: \n");
    printf("%s\n-----\n", story_last_line(size));
    char *str;
    fgets(str,sizeof(str), stdin);
    *shm_pt = strlen(str);
    shmdt(shm_pt); // gets address of shm
    int fd = open("story", O_APPEND | O_RDWR);
    write(fd, str, strlen(str) - 1);
    up_sem(1);
  }
}
