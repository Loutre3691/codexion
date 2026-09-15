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
        if (result > (LLONG_MAX - (str[i] - '0')) / 10)
        {
            // overflow détecté ICI, avant qu'il n'arrive
            printf("%s %d\n", "ERROR: the seven first arguments must be inf at INT_MAX:", INT_MAX);
            exit(1);
        }
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

void    sort_parsing(int arg, int argc, char **argv, t_data *data)
{
    while (arg < argc)
    {
        if (arg == 1)
            data->number_of_coders          = ft_parsing_nbr_coders(argv[1]);
        else if (arg == 2)
            data->time_to_burnout           = ft_parsing(argv[2]);
        else if (arg == 3)
            data->time_to_compile           = ft_parsing(argv[3]);
        else if (arg == 4)
            data->time_to_debug             = ft_parsing(argv[4]);
        else if (arg == 5)
            data->time_to_refactor          = ft_parsing(argv[5]);
        else if (arg == 6)
            data->number_of_compile_required = ft_parsing(argv[6]);
        else if (arg == 7)
            data->cooldown           = ft_parsing(argv[7]);
        else if (arg == 8)
            data->scheduler                 = ft_parsing_scheduler(argv[8]);

        arg++;
    }
}

