#include "codexion.h"

/* ajout du coder a la list fifo*/
void    add_fifo(t_coder *coder)
{
    int i;

    pthread_mutex_lock(&coder->data->scheduler.mutex_compteur);
    i = coder->data->scheduler.compteur;
    coder->data->scheduler.list_fifo[i] = coder->id;
    coder->data->scheduler.compteur++;
    pthread_mutex_unlock(&coder->data->scheduler.mutex_compteur);
}

bool    check_fifo(t_coder *coder)
{
    bool check;

    check = false; 
    pthread_mutex_lock(&coder->data->scheduler.mutex_compteur);
    if (coder->id == coder->data->scheduler.list_fifo[0])
        check = true;
    pthread_mutex_unlock(&coder->data->scheduler.mutex_compteur); 
    return check;
}

/* retire le premier coder de la file : decale chaque case d'un cran
vers la gauche, puis diminue le compteur (protege par mutex_compteur) */
void   remove_first_fifo(t_coder *coder)
{
    int i;

    pthread_mutex_lock(&coder->data->scheduler.mutex_compteur);
    i = 0;
    while( i < coder->data->scheduler.compteur - 1)
    {
        coder->data->scheduler.list_fifo[i] = coder->data->scheduler.list_fifo[i + 1];
        i++;
    }
    coder->data->scheduler.compteur--;
    pthread_mutex_unlock(&coder->data->scheduler.mutex_compteur);

}



