/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** my_functions_bis.c
*/

#include "../../include/my.h"

char *concat_str(char const *str1, char const *str2)
{
    int len_str1 = my_strlen(str1);
    int len_str2 = my_strlen(str2);
    char *result = malloc(sizeof(char) * (len_str1 + len_str2 + 2));
    result[len_str1 + len_str2 + 1] = 0;
    int i = 0;

    for (; i < len_str1; i++)
        result[i] = str1[i];
    for (int j = 0; j < len_str2; j++) {
        result[i] = str2[j];
        i++;
    }
    result[i] = '\0';
    return result;
}

int compare_strings(char const *str1, char const *str2)
{
    if (my_strlen(str1) != my_strlen(str2))
        return 0;
    for (int i = 0; str1[i]; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}

int my_str_to_int(char *str)
{
    int result = 0;
    int sign = 1;
    int found = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '-')
            sign *= -1;
        while (str[i] >= '0' && str[i] <= '9') {
            result *= 10;
            result += str[i] - '0';
            found = 1;
            i++;
        }
        if (found)
            break;
    }
    return result * sign;
}

char *my_str_cat(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    char *res = malloc(sizeof(char) * (len1 + len2 + 1));
    int j = 0;

    for (; str1[j]; j++)
        res[j] = str1[j];
    for (int i = 0; str2[i]; i++) {
        res[j] = str2[i];
        j++;
    }
    res[j] = '\0';
    return res;
}

bool my_str_comp(char *str1, char *str2)
{
    if (my_strlen(str1) != my_strlen(str2))
        return false;
    for (int i = 0; str1[i]; i++) {
        if (str1[i] != str2[i])
            return false;
    }
    return true;
}
