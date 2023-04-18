/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** builtins.c
*/

#include "../../include/my.h"

int check_builtin(char const *command)
{
    char *builtins_list[7] = {
        "cd",
        "setenv",
        "unsetenv",
        "env",
        "exit",
        "echo",
        0
    };

    for (int i = 0; builtins_list[i]; i++) {
        if (compare_strings(builtins_list[i], command))
            return i;
    }
    return -1;
}

void end_builtin_pipe(void)
{
    if (shell_var.create_filedes == false)
        return;

    close(shell_var.filedes[1]);
    dup2(shell_var.old_stdout, STDOUT_FILENO);
    close(shell_var.old_stdout);
    close_pipe();
}

void execute_builtings_bis(
    char const **arg,
    list_struct *env_ll,
    int built_index
    )
{
    int args_len = my_array_len((char **)arg);

    if (built_index == SETENV) {
        if (setenv_error_gest((char **)arg, env_ll))
            return end_builtin_pipe();
        if (args_len == 2)
            setenv_function(env_ll, (char *)arg[1], "");
        if (args_len == 3)
            setenv_function(env_ll, (char *)arg[1], (char *)arg[2]);
    }
    if (built_index == UNSETENV)
        unsetenv_function(env_ll, (char **)arg);

    return end_builtin_pipe();
}

int echo_will_fork(int built_index, char **arg)
{
    if (built_index != ECHO)
        return 0;

    if (my_array_len(arg) > 1 && my_strlen(arg[1]) >= 2) {
        if (arg[1][0] == '$' && arg[1][1] == '?' && arg[1][2] == '\0') {
            return 0;
        }
    }
    return 1;
}

void execute_builtins(
    char const *command,
    char const **arg,
    list_struct *env_ll,
    char *PATH
    )
{
    int built_index;

    if ((built_index = check_builtin(command)) == -1)
        return;
    if (shell_var.create_filedes == true && !echo_will_fork(built_index, arg)) {
        open_pipe();
        shell_var.old_stdout = dup(STDOUT_FILENO);
        dup2(shell_var.filedes[1], STDOUT_FILENO);
    }

    if (built_index == CD)
        cd_function(arg, env_ll);
    if (built_index == EXIT)
        exit_function(arg);
    if (built_index == ENV)
        env_function(env_ll);
    if (built_index == ECHO)
        echo_function(env_ll, (char **)arg, PATH);
    return execute_builtings_bis(arg, env_ll, built_index);
}
