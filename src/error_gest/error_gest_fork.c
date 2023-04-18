/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** error_gest_fork.c
*/

#include "../../include/my.h"

void error_gest_fork_crash(char *command)
{
    if (errno == 8) {
        my_putstr_err(command);
        my_putstr_err(": Exec format error. Binary file not executable.\n");
        shell_var.exit_status = 1;
    }
    if (errno == EFAULT) {
        my_putstr_err(command);
        my_putstr_err(": Bad address.\n");
        shell_var.exit_status = errno;
    }
    if (errno == ELOOP) {
        my_putstr_err(command);
        my_putstr_err(": Too many symbolic links encountered.\n");
        shell_var.exit_status = errno;
    }
    if (errno == ETXTBSY) {
        my_putstr_err(command);
        my_putstr_err(": Text file busy.\n");
        shell_var.exit_status = errno;
    }
}

void error_gest_fork(int status, char *command)
{
    if (WIFSIGNALED(status)) {
        shell_var.exit_status = WIFSIGNALED(status);
        if (WTERMSIG(status)) {
            shell_var.exit_status = 128 + WTERMSIG(status);
            my_putstr_err("Segmentation fault");
        }
        if (WIFCORED(status))
            my_putstr_err(" (core dumped)");
        if (WTERMSIG(status))
            my_putstr_err("\n");
        return;
    }
}
