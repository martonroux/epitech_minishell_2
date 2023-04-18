/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** arg_2.c
*/

#include "../../include/my.h"

func_t char_is_func(char arg)
{
    func_t func = NONE;

    if (arg == ';')
        func = SEPARATOR;
    if (arg == '|')
        func = PIPE;
    if (arg == '>')
        func = SIMPLE_REDIRECT_RIGHT;
    if (arg == '<')
        func = SIMPLE_REDIRECT_LEFT;
    return func;
}

bool is_in_array(char **array, char *sep)
{
    for (int i = 0; array[i]; i++) {
        if (my_str_comp(array[i], sep) == true)
            return true;
    }
    return false;
}

bool char_is_in_str(char *str, char c)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == c)
            return true;
    }
    return false;
}

char **args_without_newline(char *argv)
{
    char **result = get_args(argv);
    int len;

    if (shell_var.unmatched == true)
        return NULL;
    for (int i = 0; result[i]; i++) {
        len = my_strlen(result[i]);
        if (result[i][len - 1] == '\n')
            result[i][len - 1] = '\0';
    }
    return result;
}

char *local_to_malloc_word(char word[4096])
{
    if (word[0] == '\0')
        return NULL;
    char *new_word = malloc(sizeof(char) * my_strlen(word));

    for (int i = 0; word[i]; i++)
        new_word[i] = word[i];
    new_word[my_strlen(word)] = '\0';
    return new_word;
}
