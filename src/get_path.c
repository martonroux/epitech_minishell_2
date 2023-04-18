/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** get_path.c
*/

#include "../include/my.h"

void path_error_gest(char *path)
{
    if (access(path, F_OK) != -1 && access(path, X_OK) == -1) {
        my_putstr_err(path);
        my_putstr_err(": Permission denied.\n");
    } else {
        my_putstr_err(path);
        my_putstr_err(": Command not found.\n");
    }
    shell_var.exit_status = 1;
}

char *get_path_bis(char *command)
{
    if (access(command, X_OK) == -1) {
        path_error_gest(command);
        return NULL;
    }

    struct stat buf;

    stat(command, &buf);

    if (S_ISDIR(buf.st_mode)) {
        my_putstr_err(command);
        my_putstr_err(": Permission denied.\n");
        shell_var.exit_status = 1;
        return NULL;
    }
    if (my_str_contains(command, "/"))
        return command;
    return command;
}

char *get_new_path(char *PATH, char *command)
{
    if (PATH == NULL) return NULL;
    char *temp = malloc(sizeof(char) * my_strlen(PATH));
    char *result;
    int i = 0;

    for (; PATH[i] && PATH[i] != ':'; i++)
        temp[i] = PATH[i];
    if (command[0] != '/') {
        temp[i] = '/';
        temp[i + 1] = '\0';
    } else {
        temp[i] = '\0';
    }
    result = concat_str(temp, command);
    if (access(result, X_OK) == -1)
        return NULL;
    return result;
}

char *get_path(char *command, char *PATH)
{
    char *result = {0};

    if (command[0] == '.' && command[1] == '/') return get_path_bis(command);
    if (access(command, X_OK) != -1 && get_path_bis(command) != NULL)
        return command;
    PATH += 5;
    while (PATH != NULL) {
        if ((result = get_new_path(PATH, command)) != NULL)
            return result;
        while (*PATH && *PATH != ':')
            PATH++;
        if (*PATH == 0)
            break;
        PATH++;
    }
    if (access(result, X_OK) == -1) {
        path_error_gest(command);
        return NULL;
    }
    return result;
}
