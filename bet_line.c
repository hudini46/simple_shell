#include "shell.h"

/**
 * read_input - Read input from the user into a buffer.
 * @buffer: The buffer to store the input.
 * @bufsize: The size of the buffer.
 * Return: Number of characters read, or -1 on failure.
 */
ssize_t read_input(char *buffer, size_t bufsize)
{
	ssize_t chars_read = read(STDIN_FILENO, buffer, bufsize);
	if (chars_read < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	return (chars_read);
}

/**
 * read_and_expand_line - Read and expand the line of input from the user.
 * @buffer: The buffer to store the input.
 * Return: The expanded line of input entered by the user.
 */
char *read_and_expand_line(char *buffer)
{
	static size_t buffer_pos;
	static ssize_t chars_read;
	char *line = NULL;
	size_t line_len = 0;
	char current_char;

	while (1)
	{
		if (buffer_pos >= (size_t)chars_read)
		{
			chars_read = read_input(buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (chars_read == 0)
			{
				if (line_len == 0)
				{
					putchar('\n');
					return (NULL);
				}
				break;
			}
		}

		current_char = buffer[buffer_pos++];

		if (current_char == '\n')
			break;

		line = realloc(line, line_len + 1);
		if (line == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}

		line[line_len++] = current_char;
	}

	if (line != NULL)
	{
		line = realloc(line, line_len + 1);
		if (line == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		line[line_len] = '\0';
	}

	return (line);
}

/**
 * bet_line - Read a line of input from the user.
 * Return: The line of input entered by the user.
 */
char *bet_line()
{
	static char buffer[BUFFER_SIZE];

	return (read_and_expand_line(buffer));
}
