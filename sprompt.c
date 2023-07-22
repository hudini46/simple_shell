#include "shell.h"

/**
* print_prompt - Printss the shell prompt
*/
void print_prompt(void)
{
	printf("%s", PROMPT);
	fflush(stdout);
}
