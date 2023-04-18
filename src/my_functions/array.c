/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** my_functions_tris.c
*/

#include "../../include/my.h"

int my_array_len(char **arr)
{
    int len = 0;

    for (; arr[len]; len++);
    return len;
}
