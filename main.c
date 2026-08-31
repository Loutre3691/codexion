#include  "codexion.h"

int main(int argc, char **argv)
{
    int arg = 1;
    long long result = 0;
    int scheduler = 0;


    if (argc != 9)
    {
        printf("%s\n", "You must give 8 arguments");
        exit(1);
    }

    while (arg < argc)
    {
        if (arg == argc - 1)
        {
            scheduler = ft_parsing_scheduler(argv[arg]);
            printf("scheduler = %s\n", scheduler == FIFO ? "fifo" : "edf");
        }

        else
            result = ft_parsing(argv[arg]);
  
        arg++;
    }
    return(0);
  
}