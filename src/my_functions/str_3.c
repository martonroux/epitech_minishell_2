/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** str_3.c
*/

#include "../../include/my.h"

bool my_str_contains(char *str, char *contains)
{
    int i;

    while (*str) {
        for (i = 0; str[i] && contains[i] && str[i] == contains[i]; i++);

        if (contains[i] == '\0')
            return true;
        str++;
    }
    return false;
}

bool is_alpha(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    return false;
}
