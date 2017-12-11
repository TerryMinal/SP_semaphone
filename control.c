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
#include "misc.h"
#define KEY 123

// opens file story
// if successful return file descriptor else return -1
int open_file() {
  int fd = open("story.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd != -1) {
    printf("Story created!\n");
    close(fd);
    return fd;
  }
  else {
    printf("Failed to open file story\n");
    print_error();
    return -1;
  }

}

int main(int argc, char *argv[]) {
  int sem_ID;
  int shm_ID;
  
  if (! strcmp(argv[1], "-c")) {
    sem_ID = create_sem();
    shm_ID = create_shm();
    int fd = open_file();
  }
  
  // case if v tag
  else if (strcmp(argv[1], "-v") == 0) {
    int fd = open("story.txt", O_RDONLY, 0644 );
    struct stat st;
    fstat(fd, &st);
    int file_size = st.st_size;
    char buffer2[file_size];
    read(fd, &buffer2, file_size);
    printf("Story:\n %s\n", buffer2);
    close(fd);
  }
  
  // case if r tag
  else if (strcmp(argv[1], "-r") == 0) {
    int fd = open("story.txt",  O_RDONLY, 0644 );
    struct stat st;
    fstat(fd, &st);
    int file_size = st.st_size;
    char buffer2[file_size];
    read(fd, &buffer2, file_size);
    printf("Story:\n %s\n", buffer2);
    close(fd);

    remove("story.txt");
    printf("Story has been removed\n"); 
    remove_sem();
    remove_shm();
  }
  
  else {
    printf("NOTHING HAPPENED\n");
  }
 
  return 0;
}
  
