#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

void ex_it(char *args[], int arg_count) {
    if (arg_count > 1) {
        int exit_status = _atoi(args[1]);
        exit(exit_status);
    } else {
        printf("Usage: exit status (status should be an integer)\n");
    }
}

