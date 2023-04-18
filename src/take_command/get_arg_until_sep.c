/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** get_arg_from_mult.c
*/

#include "../../include/my.h"

char *get_file_name_redirect(char **arg, char *sep)
{
    int i;
    char *file_name;

    for (i = 0; arg[i]; i++) {
        if (my_str_comp(arg[i], sep))
            break;
    }
    i += 1;
    file_name = arg[i];
    return file_name;
}

char **get_arg_redirect(char **arg, char *sep)
{
    char **act_arg;
    int len;
    int y = 0;
    for (len = 0; arg[len]; len++) {
        if (my_str_comp(arg[len], sep))
            continue;
        if (check_if_func(arg[len]) != NONE)
            break;
    }
    act_arg = malloc(sizeof(char *) * len);
    act_arg[len - 1] = NULL;
    for (int i = 0; arg[i] && i < len; i++) {
        if (my_str_comp(arg[i], sep)) {
            i += 1;
            continue;
        }
        act_arg[y] = arg[i];
        y++;
    }
    return act_arg;
}

char **get_arg_until_sep(char **arg, char *sep)
{
    char **new_arg;
    int i;

    if (*arg == NULL)
        return NULL;
    if (my_str_comp(arg[0], sep) == true)
        return NULL;
    for (i = 0; arg[i]; i++) {
        if (my_str_comp(arg[i], sep) == true)
            break;
    }
    new_arg = malloc(sizeof(char *) * (i + 1));
    new_arg[i] = NULL;
    for (int h = 0; arg[h] && !my_str_comp(arg[h], sep); h++) {
        new_arg[h] = arg[h];
        i++;
    }
    return new_arg;
}
