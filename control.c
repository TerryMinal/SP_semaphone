#include "control.h"

// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
}

// creates or gets memory
// if successful returns ID of it otherwise return 0
int create_shm() {
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

// gets id of shared memory
// if successful returns id, else return 0
int get_shm() {
  int ID = shmget(KEY, 1024, 0);
  if (ID != -1) {
    printf("get of shm successful. ID: %d\n", ID);
    return ID;
  }
  else {
    printf("failed to get shared memory\n");
    print_error();
    return 0;
  }
}
// give a pointer to a pointer that will store the address of shmat
// attaches address to passed pointer
// if successful return 1, else return 0
int attach_shm(void **pt) {
  *pt = shmat(get_shm(), 0, 0);
  if ( *pt != (void *) -1) {
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
  int ID = get_shm();
  int r = shmctl(ID, IPC_RMID, NULL);
  if (r != -1) {
    printf("removal of shared memory successful. ID: %d\n", ID);
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

// changes the val of the semaphore. returns the new value
int up_sem(int a) {
  int current = get_sem_val();
  int ID = get_sem();
  semctl(ID, 0, SETVAL, current + a);
  return current + a;
}

// changes the val of the semaphore. returns the new value
int down_sem(int a) {
  int current = get_sem_val();
  int ID = get_sem();
  semctl(ID, 0, SETVAL, current - a);
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
    printf("failed to remove semaphore\n");
    print_error();
    return 0;
  }
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
