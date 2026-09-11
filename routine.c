#include "codexion.h"


/* ft_compile prends juste le time_to_compile et fait attendre avec u_sleep, quand cest ecoule
on unlock le dongle gauche et droit, et mise a jour de last_compil*/
void    ft_compile(t_coder *coder)
{
    long long time_to_compile;
    long long timer; 
    
    time_to_compile = coder->data->time_to_compile * 1000;

    timer = get_time_ms() - coder->monitor->start_time;
    printf("%lld %d is compiling\n", timer, coder->id);
    usleep(time_to_compile); // met en attente le temps de time_to_compile
    
    pthread_mutex_unlock(&coder->right_dongle->mutex);
    coder->right_dongle->is_used = false;

    pthread_mutex_unlock(&coder->left_dongle->mutex);
    coder->left_dongle->is_used = false;
    

    coder->last_compil = get_time_ms();
}

void    ft_debug(t_coder *coder)
{
    long long nbr = coder->data->number_of_coders;
    printf("%lld\n", nbr);
}

void ft_refactoring(t_coder *coder)
{
    long long nbr = coder->data->number_of_coders;
    printf("%lld\n", nbr);
}
/*ctete fonction permettra de compiler, de debuger et de refactoriser*/
void    *routine_function(void *arg)
{
    t_coder *coder;
    t_data *data;

    coder = (t_coder *)arg;
    data = coder->data;



    while(coder->monitor->stop_routine == false)
    {
        dongle_used(coder);
        ft_compile(coder);
        ft_debug(coder);  
        ft_refactoring(coder);
    }

    return (NULL);
}
