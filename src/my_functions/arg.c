/*
** EPITECH PROJECT, 2023
** B-PSU
** File description:
** my_functions_5.c
*/

#include "../../include/my.h"

char *get_next_word_func(char *argv)
{
    int len = get_next_len_func(argv);
    char *word = malloc(sizeof(char) * (len + 1));

    word[len] = '\0';
    word[0] = argv[0];
    if (argv[0] == argv[1] && (argv[0] == '>' || argv[0] == '<'))
        word[1] = argv[1];
    return word;
}

char *get_next_word_normal(char *argv, int *had_quotes)
{
    int had_char = 0;
    int len = get_next_len_normal(argv);
    char *word = malloc(sizeof(char) * (len + 1));
    int word_i = 0;

    word[len] = '\0';
    for (int i = 0; is_simple_char(argv[i], had_char) && argv[i]; i++) {
        had_char = change_had_char(had_char, argv[i], had_quotes);
        if (argv[i] == '\'' && (had_char == 1 || had_char == 0))
            continue;
        if (argv[i] == '\"' && (had_char == 3 || had_char == 0))
            continue;
        word[word_i] = argv[i];
        word_i++;
    }
    if (had_char != 0)
        print_unmatched(had_char);
    return word;
}

char *get_next_word(char *argv, int *had_quotes)
{
    *had_quotes = 0;
    if (argv[0] == '\n')
        return NULL;
    if (char_is_func(argv[0])) return get_next_word_func(argv);
    return get_next_word_normal(argv, had_quotes);
}

char **get_args(char *argv)
{
    char **result = malloc(sizeof(char *) * (my_strlen(argv) + 1));
    char *new_word;
    int act_i = 0;
    int had_quotes = 0;

    shell_var.unmatched = false;
    while (*argv) {
        while (*argv == ' ' || *argv == '\t')
            argv++;
        new_word = get_next_word(argv, &had_quotes);
        if (new_word == NULL || shell_var.unmatched == true) break;

        result[act_i] = new_word;
        if (had_quotes != 0)
            argv += 2 * had_quotes;
        argv += my_strlen(new_word);
        act_i++;
    }
    result[act_i] = NULL;
    return result;
}

char *get_value_of_env_var(list_struct *env_ll, char *name)
{
    node *node = get_env_param(env_ll, name);
    char *value;
    char *full_val;

    if (node == NULL)
        return NULL;
    value = malloc(sizeof(char) * my_strlen(node->value));
    full_val = node->value;
    while (*full_val != '=' && *full_val)
        full_val++;
    if (*full_val == '=')
        full_val++;
    for (int i = 0; full_val[i]; i++) {
        value[i] = full_val[i];
    }
    return value;
}
