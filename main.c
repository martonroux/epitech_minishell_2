/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** main.c
*/

#include "include/my.h"

shell_var_t shell_var = {0};

char *get_path_from_env(char **env)
{
    char *PATH;

    for (int i = 0; env[i]; i++) {
        if (env[i][0] == 'P' && env[i][1] == 'A' &&
            env[i][2] == 'T' && env[i][3] == 'H') {
            PATH = env[i];
        }
    }
    PATH[my_strlen(PATH)] = '\0';
    return PATH;
}

int main(
    __attribute__((unused)) int argc,
    __attribute__((unused)) char **argv,
    char **env
    )
{
    char *PATH = get_path_from_env(env);
    list_struct *env_ll = env_to_ll(env);

    shell_var.to_restore = -1;
    while (true)
        take_command(env_ll, PATH);
    return 0;
}
