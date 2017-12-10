#include <stdio.h>
#include <string.h>
#include <errno.h>

// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
}
