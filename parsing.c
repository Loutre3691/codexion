#include "codexion.h"

long long ft_parsing(char *str)
{
    long long new_nbr;
    new_nbr = ft_atoi(str);

    if (!new_nbr)
        return(1);

    printf("%lld\n", new_nbr);

    return (new_nbr);
}

long long ft_parsing_schuelder(char *str)
{
    if (strcmp (str, "schuelder") != 0)
        printf("%s\n", "Error, tu dois ecrire schuelder");
    return (0);
}