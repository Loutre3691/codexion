#include  "codexion.h"

int main(int argc, char **argv)
{
    int arg = 1;

    t_data data;
    if (argc != 9)
    {
        printf("%s\n", "You must give 8 arguments");
        exit(1);
    }
    while (arg < argc)
    {
        if (arg == 1)
            data.number_of_coders          = ft_parsing_nbr_coders(argv[1]);
        else if (arg == 2)
            data.time_to_burnout           = ft_parsing(argv[2]);
        else if (arg == 3)
            data.time_to_compile           = ft_parsing(argv[3]);
        else if (arg == 4)
            data.time_to_debug             = ft_parsing(argv[4]);
        else if (arg == 5)
            data.time_to_refactor          = ft_parsing(argv[5]);
        else if (arg == 6)
            data.number_of_compile_required = ft_parsing(argv[6]);
        else if (arg == 7)
            data.dongle_cooldown           = ft_parsing(argv[7]);
        else if (arg == 8)
            data.scheduler                 = ft_parsing_scheduler(argv[8]);

        arg++;
    }
    simulator(&data);
    return(0);
}
