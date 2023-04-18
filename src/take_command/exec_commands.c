/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** multiple_commands.c
*/

#include "../../include/my.h"

int child_actions(char *path, char **arg, list_struct *env_ll)
{
    char **env = env_ll_to_array(env_ll);
    int ret;

    if (shell_var.create_filedes == true && shell_var.in_or_out == 1)
        dup2(shell_var.filedes[1], STDOUT_FILENO);
    if (shell_var.create_filedes == true && shell_var.in_or_out == 2) {
        dup2(shell_var.new_stdin, STDIN_FILENO);
        close(shell_var.new_stdin);
    }

    ret = execve(path, arg, env);
    if (shell_var.create_filedes == true)
        close(shell_var.filedes[0]);
    if (ret == -1) {
        error_gest_fork_crash(path);
        exit(84);
    }
    exit(0);
}

void open_pipe(void)
{
    int filedes[2];

    pipe(filedes);
    shell_var.filedes[0] = filedes[0];
    shell_var.filedes[1] = filedes[1];
}

void close_pipe(void)
{
    shell_var.create_filedes = false;
    if (shell_var.in_or_out == 1)
        close(shell_var.filedes[1]);
    else
        close(shell_var.filedes[0]);
}

void restore(void)
{
    dup2(shell_var.to_restore, STDIN_FILENO);
    close(shell_var.to_restore);
    shell_var.to_restore = -1;
}

void execute_single_command(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    )
{
    if (check_builtin(arg[0]) != -1 && !skip_builtin)
        return execute_builtins(arg[0], (char const **) arg, env_ll, PATH);
    char *path = get_path(arg[0], PATH);
    if (path == NULL) return;
    if (shell_var.create_filedes == true) open_pipe();
    int status;
    int child_pid = fork();
    int ret = -1;

    if (child_pid == 0) ret = child_actions(path, arg, env_ll);
    if (ret == 0) exit(0);
    waitpid(child_pid, &status, 0);
    shell_var.exit_status = WEXITSTATUS(status);
    if (WEXITSTATUS(status) == 84) shell_var.exit_status = 1;
    if (WEXITSTATUS(status) != 1)
        if (!WIFEXITED(status)) error_gest_fork(status, path);
    if (shell_var.create_filedes == true) close_pipe();
    if (shell_var.to_restore != -1) restore();
}
