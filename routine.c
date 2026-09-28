#include "codexion.h"

/* ft_compile prends juste le time_to_compile,mise a jour de last_compil, fait attendre avec u_sleep,
quand cest ecoule on unlock le dongle gauche et droit */
void    ft_compile(t_coder *coder)
{
    long long time_to_compile;
    long long timer; 
    
    time_to_compile = coder->data->time_to_compile * 1000;
    pthread_mutex_lock(&coder->monitor->print_mutex);
    timer = get_time_ms() - coder->monitor->start_time;
    if (coder->monitor->stop_routine == true)
    {
        put_down_dongles(coder);
        pthread_mutex_unlock(&coder->monitor->print_mutex);
        return;
    }
    printf("\033[1;38;2;0;250;50m%lld %d is compiling\n\033[00m", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);

    pthread_mutex_lock(&coder->mutex_last_compil);
    coder->last_compil = get_time_ms();
    pthread_mutex_unlock(&coder->mutex_last_compil); 
    usleep(time_to_compile); // met en attente le temps de time_to_compile

    put_down_dongles(coder);

    pthread_mutex_lock(&coder->mutex_last_compil);
    coder->nb_compil++; // le mettre ici permer de + lenb compile pour le data nbr compile
    pthread_mutex_unlock(&coder->mutex_last_compil);
}


void    ft_debug(t_coder *coder)
{
    long long time_to_debug;
    long long timer;

    time_to_debug = coder->data->time_to_debug * 1000;
    pthread_mutex_lock(&coder->monitor->print_mutex);
    timer = get_time_ms() - coder->monitor->start_time;

    if (coder->monitor->stop_routine == true)
    {
        pthread_mutex_unlock(&coder->monitor->print_mutex);
        return;
    }
    printf("\033[1;38;2;200;0;200m%lld %d is debuging\n\033[00m", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);

    usleep(time_to_debug);  
}

void    ft_refactoring(t_coder *coder)
{
    long long time_to_refactor;
    long long timer;

    time_to_refactor = coder->data->time_to_refactor * 1000;
    pthread_mutex_lock(&coder->monitor->print_mutex);
    timer = get_time_ms() - coder->monitor->start_time;

    if (coder->monitor->stop_routine == true)
    {
        pthread_mutex_unlock(&coder->monitor->print_mutex);
        return;
    }
    printf("\033[1;38;2;0;100;255m%lld %d is refactoring\n\033[00m", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);

    usleep(time_to_refactor);
    
}

/* cette fonction permettra de compiler, de debuger et de refactoriser */
void    *routine_function(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    if (coder->data->number_of_coders == 1)
    {
        left_dongle_used(coder);
        while(coder->monitor->stop_routine == false)
            usleep(1000); // pause pour laisser un temps off de 0,001 secondes
        pthread_mutex_unlock(&coder->left_dongle->mutex);
    }
    while(coder->monitor->stop_routine == false)
    {
        dongle_used(coder);
        ft_compile(coder);
        if (coder->monitor->stop_routine == true)
            break;
        ft_debug(coder);
        if (coder->monitor->stop_routine == true)
            break;
        ft_refactoring(coder);
    }
    return (NULL);
}
