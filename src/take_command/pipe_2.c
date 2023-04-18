/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** pipe_2.c
*/

#include "../../include/my.h"

int nb_pipes(char **arg)
{
    int nb = 0;

    for (int i = 0; arg[i]; i++) {
        if (check_if_func(arg[i]) != NONE && check_if_func(arg[i]) != PIPE)
            break;
        if (check_if_func(arg[i]) == PIPE)
            nb++;
    }
    return nb;
}

int len_pipe_arg(char **arg)
{
    int len = 0;
    int nb_pipe = nb_pipes(arg);

    for (int i = 0; arg[i] && nb_pipe > 0; i++) {
        if (check_if_func(arg[i]) == PIPE)
            nb_pipe--;
        len++;
    }
    return len;
}

char **get_last_command(char **arg)
{
    char **new;
    int len;

    for (len = 0; arg[len]; len++) {
        if (check_if_func(arg[len]) != NONE)
            break;
    }
    new = malloc(sizeof(char *) * (len + 1));

    for (int i = 0; i < len; i++) {
        new[i] = arg[i];
    }
    return new;
}

void dup_all(int in_fd, int fd[2])
{
    dup2(in_fd, STDIN_FILENO);
    close(in_fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
}
