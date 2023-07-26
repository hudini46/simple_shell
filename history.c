#include "shell.h"

char *getHistoryFile(info_t *info)
{
	char *path, *homeDir;

	homeDir = getEnvironmentVariable(info, "HOME=");
	if (!homeDir)
		return NULL;

	path = malloc(sizeof(char) * (strlen(homeDir) + strlen(HIST_FILE) + 2));
	if (!path)
		return NULL;

	path[0] = '\0';
	strcpy(path, homeDir);
	strcat(path, "/");
	strcat(path, HIST_FILE);
	return path;
}

int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		writeToFile(node->str, fd);
		writeToFile("\n", fd);
	}

	writeToFile(BUF_FLUSH, fd);
	close(fd);
	return 1;
}

int readHistory(info_t *info)
{
	int i, last = 0, lineCount = 0;
	ssize_t fd, rdLen, fileSize = 0;
	struct stat st;
	char *buffer = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return 0;

	if (!fstat(fd, &st))
		fileSize = st.st_size;

	if (fileSize < 2)
		return 0;

	buffer = malloc(sizeof(char) * (fileSize + 1));
	if (!buffer)
		return 0;

	rdLen = read(fd, buffer, fileSize);
	buffer[fileSize] = '\0';
	if (rdLen <= 0)
		return (free(buffer), 0);

	close(fd);

	for (i = 0; i < fileSize; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			buildHistoryList(info, buffer + last, lineCount++);
			last = i + 1;
		}
	}

	if (last != i)
		buildHistoryList(info, buffer + last, lineCount++);

	free(buffer);
	info->histCount = lineCount;

	while (info->histCount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	renumberHistory(info);
	return info->histCount;
}

int buildHistoryList(info_t *info, char *buffer, int lineCount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	addNodeEnd(&node, buffer, lineCount);

	if (!info->history)
		info->history = node;

	return 0;
}

int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->histCount = i;
}

