#include "codexion.h"


void *routine_function(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    printf("%d\n", coder->id);
    return (NULL);
}