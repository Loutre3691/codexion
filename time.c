#include "codexion.h"

/* Lit l'heure ACTUELLE (dépend de gettimeofday, change à chaque appel)
return les seconde en milliseconde + les microse seconde en milliseconde
*/
long long   get_time_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* transforme un long long en structure timespec pour remettre en seconde*/

struct timespec  get_time_s(long long *deadline)
{
    struct timespec ts;

    ts.tv_sec = *deadline / 1000; // division pour passer de milli en sec
    ts.tv_nsec = (*deadline % 1000) * 1000000; // recuperer le reste et le change en nano

    return (ts);
}
