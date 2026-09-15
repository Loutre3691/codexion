#include "codexion.h"

/*
IL est important d'initialiser tous les mutex et les cond (les dongles ici) avant de create_coders
*/
void    init_t_dongle(t_dongle *dongles, t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_init(&dongles[i].mutex, NULL);
        pthread_cond_init(&dongles[i].cond, NULL);
        dongles[i].id = i; // pas obligatoire juste pour debug
        dongles[i].is_used = false;
        dongles[i].last_used = get_time_ms();
        i++;
    }
}

/*
Boucle pour detruire les mutex et cond des dongles, il est essentiel de creer 
une nouvelle boucle pour ne pas bloquer les dongles des coders voisin
qui n'auraient pas finis de travailler
*/
void    destroy_dongles(t_data *data, t_dongle *dongles)
{    
    int i;

    i = 0;
    while(i < data->number_of_coders)
    {
        pthread_mutex_destroy(&dongles[i].mutex);
        pthread_cond_destroy(&dongles[i].cond);
        i++;
    }
}

void    right_dongle_used(t_coder *coder)
{
    long long       timer;
    long long       cooldown;
    long long       deadline;
    struct timespec deadline_ts;

    cooldown = coder->data->cooldown * 1000;
    deadline = coder->right_dongle->last_used + cooldown;
    deadline_ts = get_time_s(&deadline);

    pthread_mutex_lock(&coder->right_dongle->mutex);
    while(get_time_ms() < deadline)
        pthread_cond_timedwait(&coder->right_dongle->cond, &coder->right_dongle->mutex, &deadline_ts);

    coder->right_dongle->is_used = true;
    timer = get_time_ms() - coder->monitor->start_time;

    pthread_mutex_lock(&coder->monitor->print_mutex);
    printf("%lld %d has taken a dongle\n", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);
}

void    left_dongle_used(t_coder *coder)
{
    long long       timer;
    long long       cooldown;
    long long       deadline;
    struct timespec deadline_ts;

    cooldown = coder->data->cooldown * 1000;
    deadline = coder->left_dongle->last_used + cooldown;
    deadline_ts = get_time_s(&deadline);

    pthread_mutex_lock(&coder->left_dongle->mutex);

    while(get_time_ms() < deadline)
        pthread_cond_timedwait(&coder->left_dongle->cond, &coder->left_dongle->mutex, &deadline_ts);

    coder->left_dongle->is_used = true;
    timer = get_time_ms() - coder->monitor->start_time;

    pthread_mutex_lock(&coder->monitor->print_mutex);
    printf("%lld %d has taken a dongle\n", timer, coder->id);
    pthread_mutex_unlock(&coder->monitor->print_mutex);
}

/* fonction qui de leur atribuer les dongles selon le modulo de chaque id pour 
eviter que tous le monde commence avec le dongle de droite
*/
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
