#include "codexion.h"

void    dongle_used(t_coder *coder)
{
    bool right_used;
    bool left_used;

    t_dongle *right_dongle = coder->right_dongle;
    t_dongle *left_dongle = coder->left_dongle;
    right_used = right_dongle->is_used;
    left_used = left_dongle->is_used;

    while(right_used == false && left_used == false)
    {
        if (right_used == false)
        {
            pthread_mutex_lock(&right_dongle->mutex);
            right_used = true;
        }
        if (left_used == false)
        {
            pthread_mutex_lock(&left_dongle->mutex);
            left_used = true;
        }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
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


    last_time = time_now - coder->last_compil;
    deadline_burnout = coder->last_compil + (coder->data->time_to_burnout * 1000);

    // recuperation de la structure avec seconde et nano sec de deadline pour la suite
    struct timespec deadline_s = get_time_s(&deadline_burnout);

    // fonction condition pour attendre un temps defini avec la struct deadline en seconde
    // 
    pthread_cond_timedwait(&coder->monitor->stop_cond, &coder->monitor->stop_mutex, &deadline_s);

    time_now = get_time_ms();
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
