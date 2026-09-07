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
            printf("%s\n", "ERROR: the seven first arguments must be a int positif");
            exit(1);
        }
        else
            result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}
 
long long ft_parsing(char *str)
{
    long long new_nbr;
    new_nbr = ft_atoi(str);

    if (new_nbr > INT_MAX)
    {
        printf("%s %d\n", "ERROR: the seven first arguments must be inf at INT_MAX:", INT_MAX);
        exit(1);
    }

    return (new_nbr);
}

long long ft_parsing_nbr_coders(char *str)
{
    long long new_nbr;
    new_nbr = ft_atoi(str);

    if (new_nbr > INT_MAX)
    {
        printf("%s %d\n", "ERROR: the seven first arguments must be inf at INT_MAX:", INT_MAX);
        exit(1);
    }

    if (!new_nbr)
    {
        printf("%s\n", "ERROR: the seven first arguments must be min 1");
        exit(1);
    }

    return (new_nbr);
}

int ft_parsing_scheduler(char *str)
{
    if (strcmp(str, "fifo") == 0)
        return (FIFO);
    if (strcmp(str, "edf") == 0)
        return (EDF);

    printf("%s\n", "ERROR: scheduler must be exactly \"fifo\" or \"edf\"");
    exit(1);
}