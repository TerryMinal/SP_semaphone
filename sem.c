// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
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
