/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** separator.c
*/

#include "../../include/my.h"

int exec_separator(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    )
{
    char **act_arg;

    act_arg = get_arg_until_sep(arg, ";");
    if (act_arg == NULL)
        return 1;
    execute_single_command(act_arg, env_ll, PATH, skip_builtin);

    return my_array_len(act_arg);
}
