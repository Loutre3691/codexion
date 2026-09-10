#include "codexion.h"

/* fonction qui de leur atribuer les dongles selon le modulo de chaque id pour 
eviter que tous le monde commence avec le dongle de droite
*/
void    dongle_used(t_coder *coder)
{

    if (coder->id % 2 == 0)
    {
        pthread_mutex_lock(&coder->right_dongle->mutex);
        coder->right_dongle->is_used = true;
        pthread_mutex_lock(&coder->left_dongle->mutex);
        coder->left_dongle->is_used = true;
    }
    else
    {
        pthread_mutex_lock(&coder->left_dongle->mutex);
        coder->left_dongle->is_used = true;
        pthread_mutex_lock(&coder->right_dongle->mutex);
        coder->right_dongle->is_used = true;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

}

void    ft_compile(t_coder *coder)
{
    long long time_now;
    long long time_to_compile;
    long long deadline_burnout;
    long long last_time; // temps ecoule depuis derniere action
    
    time_now = get_time_ms();
    time_to_compile = coder->data->time_to_compile * 1000;
   
    pthread_mutex_init(&coder->monitor->stop_mutex, NULL);

    while(coder->monitor->stop_routine == false)
    {
        pthread_mutex_lock(&coder->monitor->stop_mutex);
        last_time = time_now - coder->last_compil;
        deadline_burnout = coder->last_compil + (coder->data->time_to_burnout * 1000);

        // recuperation de la structure avec seconde et nano sec de deadline pour la suite
        struct timespec deadline_s = get_time_s(&deadline_burnout);

        /*met le thread en pause. Il se réveille: deadline atteinte, soit autre thread appelle 
        broadcast/signal sur stop_cond. stop_mutex est liberer le temsp de lattente et reverouille
        apres*/
        pthread_cond_timedwait(&coder->monitor->stop_cond, &coder->monitor->stop_mutex, &deadline_s);
    }

    pthread_mutex_unlock(&coder->monitor->stop_mutex);
    coder->last_compil = time_now;
}


/*ctete fonction permettra de compiler, de debuger et de refactoriser*/
void    *routine_function(void *arg)
{
    t_coder *coder;
    t_data *data;

    coder = (t_coder *)arg;
    data = coder->data;

    dongle_used(coder);
    ft_compile(coder);


    return (NULL);
}
