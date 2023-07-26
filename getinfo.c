#include "shell.h"

char **getEnvironment(info_t *info)
{
    if (!info->env || info->envChanged)
    {
        info->env = listToStrings(info->envList);
        info->envChanged = 0;
    }

    return info->env;
}

int unsetEnvironmentVariable(info_t *info, char *variable)
{
    list_t *node = info->envList;
    size_t i = 0;
    char *p;

    if (!node || !variable)
        return 0;

    while (node)
    {
        p = startsWith(node->string, variable);
        if (p && *p == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->envList), i);
            i = 0;
            node = info->envList;
            continue;
        }
        node = node->next;
        i++;
    }
    return info->envChanged;
}

int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!variable || !value)
        return 0;

    buf = malloc(_strlen(variable) + _strlen(value) + 2);
    if (!buf)
        return 1;
    _strcpy(buf, variable);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->envList;
    while (node)
    {
        p = startsWith(node->string, variable);
        if (p && *p == '=')
        {
            free(node->string);
            node->string = buf;
            info->envChanged = 1;
            return 0;
        }
        node = node->next;
    }
    addNodeEnd(&(info->envList), buf, 0);
    free(buf);
    info->envChanged = 1;
    return 0;
}
