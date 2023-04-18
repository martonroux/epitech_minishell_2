/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** arg_3.c
*/

#include "../../include/my.h"

int change_had_char(int had_char, char c, int *had_quotes)
{
    if (c == '\'') {
        if (had_char == 3) return 3;
        if (had_char == 1) {
            *had_quotes += 1;
            return 0;
        }
        if (had_char == 0) return 1;
    }
    if (c == '"') {
        if (had_char == 3) {
            *had_quotes += 1;
            return 0;
        }
        if (had_char == 1) return 1;
        if (had_char == 0) return 3;
    }
    return had_char;
}

void print_unmatched(int had_char)
{
    if (had_char == 3)
        my_putstr_err("Unmatched '\"'.\n");
    else
        my_putstr_err("Unmatched '\''.\n");
    shell_var.exit_status = 1;
    shell_var.unmatched = true;
}

bool is_simple_char(char c, int skip_space_tabs)
{
    if (skip_space_tabs != 0)
        return true;
    if (char_is_func(c))
        return false;
    if (c == ' ' || c == '\t')
        return false;
    return true;
}

int get_next_len_func(char *argv)
{
    int len = 0;

    len += 1;
    if (argv[0] == argv[1] && (argv[0] == '>' || argv[0] == '<'))
        len += 1;
    return len;
}

int get_next_len_normal(char *argv)
{
    int had_char = 0;
    int *had_quotes = malloc(sizeof(int) * 2);
    int temp_i = 0;

    for (int i = 0; is_simple_char(argv[i], had_char) && argv[i]; i++) {
        had_char = change_had_char(had_char, argv[i], had_quotes);
        if (argv[i] == '\'' && (had_char == 1 || had_char == 0))
            continue;
        if (argv[i] == '\"' && (had_char == 3 || had_char == 0))
            continue;
        temp_i++;
    }
    free(had_quotes);
    return temp_i;
}
