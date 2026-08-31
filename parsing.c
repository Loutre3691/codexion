#include "codexion.h"

long long ft_parsing(char *str)
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