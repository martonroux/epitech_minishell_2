/*
** EPITECH PROJECT, 2023
** B-PSU
** File description:
** my_functions_quad.c
*/

#include "../../include/my.h"

char **env_ll_to_array(list_struct *env_ll)
{
    char **array;
    node *actual = env_ll->first;
    int nb_elems = 0;

    while (actual != NULL) {
        nb_elems++;
        actual = actual->next;
    }
    array = malloc(sizeof(char *) * (nb_elems + 1));
    array[nb_elems] = NULL;
    actual = env_ll->first;

    for (int i = 0; actual != NULL; i++) {
        array[i] = malloc(sizeof(char) * my_strlen(actual->value) + 1);
        array[i] = actual->value;
        actual = actual->next;
    }
    return array;
}

char *get_name_env(char *full_value)
{
    int len = 0;
    char *name;

    for (; full_value[len] && full_value[len] != '='; len++);
    if (full_value[len] == '\0')
        return NULL;

    name = malloc(sizeof(char) * (len + 1));
    name[len] = '\0';

    for (int i = 0; i < len; i++)
        name[i] = full_value[i];
    return name;
}

node *get_env_param(list_struct *head, char *name)
{
    node *actual = head->first;
    char *act_name;

    while (actual != NULL) {
        act_name = get_name_env(actual->value);
        if (my_str_comp(act_name, name)) {
            return actual;
        }
        actual = actual->next;
    }
    return NULL;
}

int setenv_error_gest_bis(char **args)
{
    for (int i = 1; args[1][i]; i++) {
        if (!is_alpha_num(args[1][i])) {
            my_putstr_err(
                "setenv: Variable name must contain alphanumeric characters.\n"
            );
            shell_var.exit_status = 1;
            return 1;
        }
    }
    return 0;
}

int setenv_error_gest(char **args, list_struct *env_ll)
{
    int len = my_array_len(args);

    if (len == 1) {
        env_function(env_ll);
        return 0;
    }
    if (len > 3) {
        my_putstr_err("setenv: Too many arguments.\n");
        shell_var.exit_status = 1;
        return 1;
    }
    if (is_alpha(args[1][0]) == false) {
        my_putstr_err("setenv: Variable name must begin with a letter.\n");
        shell_var.exit_status = 1;
        return 1;
    }
    return setenv_error_gest_bis(args);
}
