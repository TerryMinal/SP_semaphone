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

//gets the last line of the file and returns a string of it
char * story_last_line(int size, int fd) {
  char buffer[1000];
  char * buffer_ptr = buffer; 
  lseek(fd, -size, SEEK_END); //starts from end of file and work way back size bytes
  read(fd, buffer, sizeof(buffer));
  return buffer_ptr;
}

int main() {
  printf("Starting\n");
  //assumes shared memory and semaphore are already created
  down_sem(1);
  int * shm_pt = shmat(get_shm(), 0, 0);
  int size = *shm_pt;
  //printf("%d\n", size);
  int fd = open("story.txt", O_APPEND | O_RDWR);
  
  char * last_line = story_last_line(size, fd);
  printf("Last line of the story: %s\n", last_line);
  char str[10000];
  
  printf("Enter the next line: \n"); 
  fgets(str, sizeof(str), stdin);
  lseek(fd, 0, SEEK_END);
  write(fd, str, strlen(str));

  *shm_pt = strlen(str); 
  shmdt(shm_pt);
  //close(fd);
  
  up_sem(1);

  return 0; 
}
