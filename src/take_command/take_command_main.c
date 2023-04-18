/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** take_commands.c
*/

#include "../../include/my.h"

func_t check_if_func(char *arg)
{
    func_t func = NONE;

    if (compare_strings(arg, ";") == true)
        func = SEPARATOR;
    if (compare_strings(arg, "|") == true)
        func = PIPE;
    if (compare_strings(arg, ">") == true)
        func = SIMPLE_REDIRECT_RIGHT;
    if (compare_strings(arg, "<") == true)
        func = SIMPLE_REDIRECT_LEFT;
    if (compare_strings(arg, ">>") == true)
        func = COMPLEX_REDIRECT_RIGHT;
    if (compare_strings(arg, "<<") == true)
        func = COMPLEX_REDIRECT_LEFT;
    return func;
}

int command_recursive_complement(
    int func,
    char **arg,
    list_struct *env_ll,
    char *PATH
    )
{
    int offset = 0;
    exec_data_t exec_data;

    exec_data.env_ll = env_ll;
    exec_data.PATH = PATH;
    exec_data.arg = arg;
    exec_data.skip_builtin = 0;
    if (func == SEPARATOR)
        offset = exec_separator(arg, env_ll, PATH, 0);
    if (func == SIMPLE_REDIRECT_RIGHT)
        offset = exec_sr_rl(arg, env_ll, PATH, 0);
    if (func == COMPLEX_REDIRECT_RIGHT)
        offset = exec_cr_rl(arg, env_ll, PATH, 0);
    if (func == SIMPLE_REDIRECT_LEFT)
        offset = exec_sr_lr(arg, env_ll, PATH, 0);
    if (func == PIPE)
        offset = exec_pipe(exec_data);
    return offset;
}

void command_recursive(char **arg, list_struct *env_ll, char *PATH)
{
    func_t func;
    int offset;

    if (*arg == NULL)
        return;
    for (int i = 0; arg[i]; i++) {
        func = check_if_func(arg[i]);

        if (func != NONE)
            break;
    }
    if (func == NONE)
        execute_single_command(arg, env_ll, PATH, 0);

    offset = command_recursive_complement(func, arg, env_ll, PATH);

    if (offset == -1) return;
    if (my_array_len(arg) <= offset + 1) return;
    if (func != NONE)
        return command_recursive(arg + offset + 1, env_ll, PATH);
}

void take_command(list_struct *env_ll, char *PATH)
{
    int is_tty = isatty(STDIN_FILENO);
    char *command = malloc(sizeof(char) * 5001);
    char **arg;
    size_t err;
    size_t n = 5000;
    for (int i = 0; i < (int)n; i++)
        command[i] = '\0';

    if (is_tty)
        my_putstr("$> ");
    err = getline(&command, &n, stdin);
    if (err == (size_t)-1) {
        if (is_tty)
            my_putstr("exit\n");
        exit(shell_var.exit_status);
    }
    if (*command == '\n') return;
    arg = args_without_newline(command);
    if (arg == NULL) return;
    command_recursive(arg, env_ll, PATH);
}
