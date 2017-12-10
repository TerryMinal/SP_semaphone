#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "misc.h"

// prints error
void print_error() {
    printf("Error: %s\n", strerror(errno));
}
