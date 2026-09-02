#ifndef CODEXION_H
# define CODEXION_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>


// STRUCTURES

/* creation d'une structure pour definir les programmeurs et leur dongles
 chaque dongles doit etre un pointeur d'une liste de dongles, car deux programmeurs
 vont devoir utiliser le meme dongle */
typedef struct s_dongle
{
    int                 id;
    bool                is_used;
    pthread_mutex_t     mutex; // secu, verrou
    pthread_cond_t      cond; // gestion attente
    long long           last_used; // cooldown

} t_dongle;

/*creation d'un enum  pour le schuelder avec fifo et edf pour
le  8eme argument, enum valeur = int donc FIFO == 0
EDF == 1*/

typedef enum e_sched
{
    FIFO,
    EDF,
}   t_sched;


typedef struct s_data
{
    long long   number_of_coders;
    long long   time_to_burnout;
    long long   time_to_compile;
    long long   time_to_debug;
    long long   time_to_refactor;
    long long   number_of_compile_required;
    long long   dongle_cooldown;
    t_sched     scheduler;

} t_data;


typedef struct s_coder
{
    int          id;
    pthread_t    thread;
    t_data       *data; // pointeur vers ma struct data
    t_dongle     *right_dongle;
    t_dongle     *left_dongle;
    long long    last_compil; // burnout/EDF
    int          nb_compil; // compteur de compilations
} t_coder;



// FONCTIONS
long long   ft_parsing(char *str);
int         ft_parsing_scheduler(char *str);
long long   ft_atoi(char *str);
void        simulator(t_data *data);
void        *routine_function(void *arg);
void        create_coders(t_data *data, int i, t_dongle *dongles, t_coder *coders);
void        mutex_dongle(t_dongle *dongles, int i);


#endif
