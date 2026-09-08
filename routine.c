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
    long long time_to_compile;
    
    time_to_compile = get_time_ms();
    printf("%lld\n", time_to_compile);
    long long data = coder->data->number_of_coders;

    printf("%lld\n", data);

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


/*
┌─────────────────────────────────────┐
│  Boucle tant que pas fini :          │
│                                       │
│   1. Acquérir dongle gauche + droit  │ ← ici mutex_lock (attente possible)
│   2. COMPILER (time_to_compile ms)   │ ← garde les 2 dongles pendant ce temps
│   3. Libérer les 2 dongles           │ ← mutex_unlock + démarrer cooldown
│   4. nb_compil++, last_compil = now  │
│   5. DEBUG (time_to_debug ms)        │ ← pas de dongle
│   6. REFACTOR (time_to_refactor ms)  │ ← pas de dongle
│   7. → retour en haut, immédiatement │
│                                       │
└─────────────────────────────────────┘
*/