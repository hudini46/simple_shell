#ifndef GVAR_H
#define GVAR_H

#include <stddef.h>
#include <sys/types.h>

/* Declare program_name variable */
extern char *program_name;

/* Declare buffer variable */
extern char *buffer;
extern size_t bufsize;
extern ssize_t nread;

#endif
