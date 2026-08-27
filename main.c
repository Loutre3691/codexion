#include  "codexion.h"


int main(int argc, char **argv)
{
    int arg = 1;
    int *tab;

    if (argc != 9)
    {
        printf("%s\n", "You must give 8 arguments");
        return (1);
    }

    while (arg < argc)
    {
        if (arg == argc - 1)
            ft_parsing_schuelder(argv[arg]);
        else
        {
            *tab = ft_parsing(argv[arg]);
            printf("%d", *tab);
            tab++;
        }
        arg++;
    }
    return(0);
  
}