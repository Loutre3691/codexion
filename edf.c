#include "codexion.h"

/*deadline la plus proche*/
void   add_edf(t_coder *coder)
{
    int i;

    pthread_mutex_lock(&coder->data->scheduler.mutex_compteur);
    i = coder->data->scheduler.compteur;
    coder->data->scheduler.list_edf[i] = coder->id;
    coder->data->scheduler.compteur++;
    pthread_mutex_unlock(&coder->data->scheduler.mutex_compteur);
}

bool    check_edf(t_coder *coder)
{
    bool        check;
    long long   deadline;
    int         i;
    int         id;

    check = false;
    i = 0;
    pthread_mutex_lock(&coder->mutex_last_compil);
    pthread_mutex_lock(&coder->data->scheduler.mutex_compteur);

    while(i < coder->data->scheduler.compteur)
    {
        id = coder->data->scheduler.list_edf[i];
        deadline = coder[id].last_compil + (coder->data->time_to_burnout);
        i++;
    }
    pthread_mutex_unlock(&coder->mutex_last_compil);
    pthread_mutex_unlock(&coder->data->scheduler.mutex_compteur);

    return(true);
}