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
#include "sem.h"
#define KEY 123

// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
}

// opens file story
// if successful return file descriptor else return -1
int open_file() {
  int fd = open("story", O_CREAT | O_TRUNC , O_RDWR);
  if (fd != -1) {
    return fd;
  }
  else {
    printf("failed to open file story\n");
    print_error();
    return -1;
  }
}

//gets the last line of the file and returns a string of it
char * story_last_line(int size) {
  int fd = open_file();
  char *buffer;
  lseek(fd, -size, SEEK_END); //starts from end of file and work way back size bytes
  read(fd, buffer, sizeof(buffer));
  return buffer;
}

int main(int argc, char *argv[]) {
  int sem_ID;
  int shm_ID;
  int fd;
  char *par = argv[1];
  if (strcmp(par, "-c") == 0) {
    // sem_ID = create_sem(atoi(argv[2]));
    // shm_ID = create_shm();
    fd = open_file();
  }
  // case if v tag
  else if (strcmp(par, "-v") == 0) {
    // sem_ID = semget(KEY, 0, 0644);
    // get_sem_val();
    printf("%s\n", story_last_line(1000));
  }
  // case if r tag
  else if (strcmp(par, "-r") == 0) {
    // ID = = semget(KEY, 0, 0644);
    struct stat st;
    fstat(open_file(), &st);
    int file_size = st.st_size;
    // printf("%d\n", file_size);
    char *buffer2;
    read(open_file(), &buffer2, file_size);
    // remove_sem();
    // remove_shm();
  }
  else {
    printf("NOTHING HAPPENED\n");
  }
}
