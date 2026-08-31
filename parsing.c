#include "codexion.h"

long long ft_parsing(char *str)
{
    long long new_nbr;
    new_nbr = ft_atoi(str);

    if (!new_nbr)
        exit(1);

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