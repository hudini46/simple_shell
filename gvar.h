#ifndef GVAR_H
#define GVAR_H

#include <stddef.h>
#include <sys/types.h>

/* Declare program_name variable */
char *program_name;

/* Declare buffer variable */
char *buffer = NULL;
size_t bufsize = 0;
ssize_t nread;

#endif
