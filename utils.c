#include "codexion.h"

long long ft_atoi(char *str)
{
    long long result;
    int i;
    i = 0;

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
        {
            printf("%s", "ERROR: the seven first arguments must be a int positif");
            return(1);
        }
        else
            result = str[i] * 10  + (str[i] - '0');
        i++;
    }
    printf("%lld\n", result);
    return (result);
}