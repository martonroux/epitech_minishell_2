/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** free_act_arg.c
*/

#include "../../include/my.h"

void free_char_array(char **array)
{
    for (int i = 0; array[i]; i++)
        free(array[i]);
}
