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

// //gets the last line of the file and returns a string of it
// char * story_last_line(int size) {
//   int fd = open("story", O_APPEND | O_RDWR );
//   printf("%d\n", fd);
//   char buffer = calloc(size, sizeof(char ));
//   lseek(fd, -size, SEEK_END); //starts from end of file and work way back size bytes
//   printf("i seg fault \n");
//   read(fd, &buffer, size);
//   return buffer;
// }

int main() {
  //assumes shared memory and semaphore are already created
  down_sem(1);
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
  *shm_pt = strlen(str) - 1;
  shmdt(shm_pt);
  write(fd, str, strlen(str) - 1);
  up_sem(1);
}
