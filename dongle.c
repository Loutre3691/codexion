#include "codexion.h"

void    mutex_dongle(t_dongle *dongles, int i)
{
    pthread_mutex_init(&dongles[i].mutex, NULL);
}