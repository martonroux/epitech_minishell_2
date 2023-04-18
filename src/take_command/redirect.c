/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** redirect.c
*/

#include "../../include/my.h"

// sr: simple redirect
// cr: complex redirect
// rl: right-to-left
// lr: left-to-right

int redirect_error_gest(char **arg, char *redir, char **act_arg)
{
    int i = 0;

    for (; arg[i] && !my_str_comp(arg[i], redir); i++);
    i += 1;

    if (arg[i] == NULL || check_if_func(arg[i]) != NONE) {
        my_putstr_err("Missing name for redirect.\n");
        shell_var.exit_status = 1;
        return -1;
    }
    if (act_arg == NULL) {
        my_putstr_err("Invalid null command.\n");
        shell_var.exit_status = 1;
        return -1;
    }
    return 0;
}

int exec_sr_rl(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    )
{
    int fd;
    char **act_arg = get_arg_redirect(arg, ">");
    int len = my_array_len(act_arg);
    char *file_name = get_file_name_redirect(arg, ">");
    char buffer[4096];
    size_t buf_size;

    if (redirect_error_gest(arg, ">", act_arg) == -1)
        return -1;
    shell_var.create_filedes = true;
    shell_var.in_or_out = 1;

    execute_single_command(act_arg, env_ll, PATH, skip_builtin);

    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    buf_size = read(shell_var.filedes[0], buffer, sizeof(buffer));

    write(fd, buffer, buf_size);
    close(fd);
    return len + 2;
}

int exec_cr_rl(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    )
{
    int fd;
    char **act_arg = get_arg_redirect(arg, ">>");
    int len = my_array_len(act_arg);
    char *file_name = get_file_name_redirect(arg, ">>");
    char buffer[4096];
    size_t buf_size;

    if (redirect_error_gest(arg, ">>", act_arg) == -1)
        return -1;
    shell_var.create_filedes = true;
    shell_var.in_or_out = 1;

    execute_single_command(act_arg, env_ll, PATH, skip_builtin);

    fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    buf_size = read(shell_var.filedes[0], buffer, sizeof(buffer));

    write(fd, buffer, buf_size);
    close(fd);
    return len + 2;
}

int exec_sr_lr(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    )
{

    int fd;
    char **act_arg = get_arg_redirect(arg, "<");
    int len = my_array_len(act_arg);
    char *file_name = get_file_name_redirect(arg, "<");

    if (redirect_error_gest(arg, "<", act_arg) == -1)
        return -1;
    shell_var.create_filedes = true;
    shell_var.in_or_out = 2;
    fd = open(file_name, O_RDONLY);
    shell_var.new_stdin = dup(fd);

    execute_single_command(act_arg, env_ll, PATH, skip_builtin);

    return len + 2;
}
