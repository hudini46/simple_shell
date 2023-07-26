#include "shell.h"

char *copyString(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return destination;

	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
	return destination;
}

char *duplicateString(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return NULL;

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return NULL;

	for (length++; length--;)
		result[length] = *--str;

	return result;
}

void printString(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		writeCharacter(str[i]);
		i++;
	}
}

int writeCharacter(char c)
{
	static int i;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}

	if (c != BUFFER_FLUSH)
		buffer[i++] = c;

	return 1;
}

