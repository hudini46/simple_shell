#include "shell.h"

int isChainDelimiter(info_t *info, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = '\0';
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return 0;

	*position = j;
	return 1;
}

void checkChain(info_t *info, char *buffer, size_t *position, size_t i, size_t len)
{
	size_t j = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = '\0';
			j = len;
		}
	}

	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = '\0';
			j = len;
		}
	}

	*position = j;
}

int replaceAliases(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return 0;

		free(info->argv[0]);
		p = strchr(node->str, '=');
		if (!p)
			return 0;

		p = _strdup(p + 1);
		if (!p)
			return 0;

		info->argv[0] = p;
	}

	return 1;
}

int replaceVariables(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
					_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
					_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}

		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
					_strdup(strchr(node->str, '=') + 1));
			continue;
		}

		replaceString(&info->argv[i], _strdup(""));
	}

	return 0;
}

int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return 1;
}

/* Rest of the code... */

int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int isDelimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return 1;
	return 0;
}

int isAlphabeticCharacter(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}

int convertStringToInteger(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return output;
}

