#include "codexion.h"


void *routine_function(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    printf("%p\n", (void *)coder->thread);
    printf("%lu\n", (unsigned long)coder->thread);
    return (NULL);
}