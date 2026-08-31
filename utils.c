#include "codexion.h"

long long ft_atoi(char *str)
{
    long long result;
    int i;

    result = 0;
    i = 0;

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            printf("%s", "ERROR: the seven first arguments must be a int positif");
            exit(1);
        }
        else
            result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}