/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** pipe.c
*/

#include "../../include/my.h"

int exec_pipe_loop(
    exec_data_t exec_data,
    int in_fd,
    int fd[2],
    list_struct *env_ll
    )
{
    char **act_command;
    int status;
    for (int i = 0; i < nb_pipes(exec_data.arg); i++) {
        pipe(fd);
        pid_t pid = fork();
        act_command = get_arg_until_sep(exec_data.arg, "|");
        if (pid == 0) {
            dup_all(in_fd, fd);
            execute_single_command(act_command, env_ll, exec_data.PATH, 0);
            exit(shell_var.exit_status);
        }
        waitpid(pid, &status, 0);
        close(in_fd);
        in_fd = fd[0];
        close(fd[1]);
        exec_data.arg += my_array_len(act_command) + 1;
        if (WEXITSTATUS(status) != 0) break;
    }
    shell_var.exit_status = WEXITSTATUS(status);
    return in_fd;
}

int exec_pipe(exec_data_t exec_data)
{
    int save = dup(STDIN_FILENO);
    int in_fd = dup(STDIN_FILENO);
    int fd[2];
    int len = len_pipe_arg(exec_data.arg);

    shell_var.exit_status = 0;
    in_fd = exec_pipe_loop(exec_data, in_fd, fd, exec_data.env_ll);

    dup2(in_fd, STDIN_FILENO);
    close(in_fd);

    exec_data.arg += len;

    shell_var.to_restore = save;
    return len - 1;
}
