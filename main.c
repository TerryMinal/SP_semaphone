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
#define KEY 123

int main() {
  //assumes shared memory and semaphore are already created
  if (get_sem_val() <= 0) {
    printf("file current in use\n");
    while(get_sem_val() == 0) { /* blocking */ };
  }
  else {
    down_sem(1);
    int *shm_pt;
    attach_shm(&shm_pt);
    int size = *shm_pt;
    printf("%d\n", size);
    printf("%s\n", story_last_line(size));
    char *str;
    fgets(str,sizeof(str), stdin);
    // str[strlen(str) - 1] = 0; //strips \n
    *shm_pt = sizeof(str);
    write(open_file(), str, sizeof(str));
    up_sem(1);
  }
}
