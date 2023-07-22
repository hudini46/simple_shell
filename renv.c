#include "shell.h"


/**updated env.c file **/
/**
 * check_env - checks and prints the environmend variables
 * Return: environment variables
 */
void check_env(void)
{
	char **env = environ;

	while (*env)
	{
		char *equals = _strchr(*env, '=');

		if (equals != NULL)
		{
			int index = (int)(equals - *env);
			char *name = malloc((index + 1) * sizeof(char));

			if (name == NULL)
			{
				print_malloc_error();
				exit(EXIT_FAILURE);
			}

			_strncpy(name, *env, index);
			name[index] = '\0';
			printf("%s=%s\n", name, equals + 1);
			free(name);
		}

		env++;
	}
}
/**
 * _strchr - Locate charactere in string.
 * @s: The string to searcch.
 * @c: The character to loccate.
 *
 * Return: Pointer to the first occurrence of character c in string s,
 *         or NULL if the character is not find.
 */
char *_strchr(char *s, char c)
{
	return (strchr(s, c));
}

/**
 * _strncpy - Copy a string.
 * @dest: The destination buffers.
 * @src: The source string.
 * @n: The maximum numbers of characters to copy.
 *
 * Return: Pointer to the destination buffer.
 */
char *_strncpy(char *dest, char *src, int n)
{
	return (strncpy(dest, src, n));
}
