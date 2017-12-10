// prints error
void print_error();

// creates semaphore
// if successful returns its id otherwise return 0
int create_sem(int val);

// get sem value
// returns 1 if successful otherwise it returns 0
int get_sem_val();

//gets the shared memory id
// if successful return id, else return 0
int get_sem();

// changes the val of the semaphore. returns the new value
int up_sem(int a);

// changes the val of the semaphore. returns the new value
int down_sem(int a);
