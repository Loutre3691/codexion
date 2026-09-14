#include  "codexion.h"

int main(int argc, char **argv)
{
    int arg = 1;
    t_data *data;

    data = malloc(sizeof(t_data));

    if (argc != 9)
    {
        printf("%s\n", "You must give 8 arguments");
        exit(1);
    }

    sort_parsing(arg, argc, argv, data);
    simulator(data);
    return(0);
}
