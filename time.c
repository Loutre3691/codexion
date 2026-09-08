#include "codexion.h"


// Lit l'heure ACTUELLE (dépend de gettimeofday, change à chaque appel)
long long   get_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}