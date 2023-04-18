/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** my_functions.c
*/

#include "../../include/my.h"

int my_strlen(char const *str)
{
    int len = 0;

    for (; str[len]; len++);
    return len;
}

void my_putstr(char const *str)
{
    while (*str) {
        write(1, &(*str), 1);
        str++;
    }
}

void my_putstr_err(char const *str)
{
    while (*str) {
        write(2, &(*str), 1);
        str++;
    }
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

bool is_alpha_num(char c)
{
    if (c >= 'a' && c <= 'z')
        return true;
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c == '.' || c == '_')
        return true;
    if (c >= '0' && c <= '9')
        return true;
    return false;
}
