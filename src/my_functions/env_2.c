/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** env_2.c
*/

#include "../../include/my.h"

list_struct *env_to_ll(char **env)
{
    list_struct *head = ll_initialize();
    char cwd[PATH_MAX];

    for (int i = 0; env[i]; i++) {
        ll_add_first(head, env[i]);
    }
    getcwd(cwd, sizeof(cwd));
    setenv_function(head, "OLDPWD", "");
    return head;
}
