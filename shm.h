// prints error
void print_error();

// creates shared memory
// if successful returns ID of it otherwise return 0
int create_shm();

// gets id of shared memory
// if successful returns id, else return 0
int get_shm();

// give a pointer to a pointer that will store the address of shmat
// attaches address to passed pointer
// if successful return 1, else return 0
int attach_shm(int **pt);

// detaches shared memory at ID ID
// if successful return 1 otherwise return 0
int detach_shm(int **pt);

// removes shared memory at ID ID. Only successful after all last process
// detaches from it
// if successful, return 1 otherwise return 0
int remove_shm();
