/*
** EPITECH PROJECT, 2023
** B-PSU
** File description:
** shell_var.h
*/

#pragma once

#include <stdbool.h>

typedef struct shell_var_t {
    int exit_status;
    bool create_filedes;
    bool unmatched;
    int in_or_out;
    int filedes[2];
    int old_stdout;
    int new_stdin;
    int to_restore;
} shell_var_t;
