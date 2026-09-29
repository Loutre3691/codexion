#include "codexion.h"

void    put_down_dongles(t_coder *coder)
{
    coder->right_dongle->is_used = false;
    coder->right_dongle->last_used = get_time_ms();
    pthread_mutex_unlock(&coder->right_dongle->mutex);

    coder->left_dongle->is_used = false;
    coder->left_dongle->last_used = get_time_ms();
    pthread_mutex_unlock(&coder->left_dongle->mutex);
}

void    right_dongle_used(t_coder *coder)
{
    long long       timer;
    long long       cooldown;
    long long       deadline;
    struct timespec deadline_ts;

    pthread_mutex_lock(&coder->right_dongle->mutex);
    cooldown = coder->data->cooldown;
    deadline = coder->right_dongle->last_used + cooldown;
    deadline_ts = get_time_s(&deadline);

    while(get_time_ms() < deadline)
        pthread_cond_timedwait(&coder->right_dongle->cond, &coder->right_dongle->mutex, &deadline_ts);

    coder->right_dongle->is_used = true;
    pthread_mutex_lock(&coder->monitor->print_mutex);
    timer = get_time_ms() - coder->monitor->start_time;

    if (coder->monitor->stop_routine == true)
    {
        pthread_mutex_unlock(&coder->monitor->print_mutex);
        return;
    }
    printf("\033[1;30m%lld %d has taken a dongle\n\033[00m", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);
}

void    left_dongle_used(t_coder *coder)
{
    long long       timer;
    long long       cooldown;
    long long       deadline;
    struct timespec deadline_ts;

    pthread_mutex_lock(&coder->left_dongle->mutex);
    cooldown = coder->data->cooldown;
    deadline = coder->left_dongle->last_used + cooldown;
    deadline_ts = get_time_s(&deadline);
    
    while(get_time_ms() < deadline)
        pthread_cond_timedwait(&coder->left_dongle->cond, &coder->left_dongle->mutex, &deadline_ts);

    coder->left_dongle->is_used = true;
    pthread_mutex_lock(&coder->monitor->print_mutex);
    timer = get_time_ms() - coder->monitor->start_time;
    
    if (coder->monitor->stop_routine == true)
    {
        pthread_mutex_unlock(&coder->monitor->print_mutex);
        return;
    }
    printf("\033[1;30m%lld %d has taken a dongle\n\033[00m", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);
}

/* permet de prendre les dgonles selon le modulo le l id du coder 
pour eviter que tous le monde commence avec le dongle de droite */
void    dongle_used(t_coder *coder)
{
if (coder->id % 2 == 0)
    {
        right_dongle_used(coder);
        left_dongle_used(coder);
    }
    else
    {
        left_dongle_used(coder);
        right_dongle_used(coder);
    }  
}

