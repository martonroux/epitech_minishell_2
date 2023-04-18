/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** builtins_funcs.c
*/

#include "../../include/my.h"

void exit_function(char **arg)
{
    int exit_status = 0;

    if (my_array_len(arg) > 1 && check_if_func(arg[1]) == NONE) {
        if (check_if_int(arg[1]) == false) {
            my_putstr_err("exit: Expression Syntax.\n");
            shell_var.exit_status = 1;
            return;
        }
        exit_status = my_str_to_int(arg[1]);
    }
    my_putstr("exit\n");
    exit(exit_status);
}

void env_function(list_struct *env_ll)
{
    ll_print(env_ll);
    shell_var.exit_status = 0;
}

void setenv_function(
    list_struct *env_ll,
    char *name,
    char *value
    )
{
    char *full_name = my_str_cat(name, "=");
    char *full_data = my_str_cat(full_name, value);
    node *existing;

    if ((existing = get_env_param(env_ll, name)) != NULL) {
        existing->value = full_data;
        return;
    }
    ll_add_last(env_ll, full_data);
    shell_var.exit_status = 0;
}

void unsetenv_function(list_struct *env_ll, char **args)
{
    if (my_array_len(args) == 1) {
        my_putstr_err("unsetenv: Too few arguments.\n");
        shell_var.exit_status = 1;
        return;
    }
    node *to_del;

    for (int i = 1; args[i]; i++) {
        if ((to_del = get_env_param(env_ll, args[i])) == NULL)
            continue;
        ll_delete(env_ll, to_del);
    }
    shell_var.exit_status = 0;
}
