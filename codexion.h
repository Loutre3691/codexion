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

// creation d'un enum  pour le schuelder avec fifo et edf pour
// le  8eme argument, enum valeur = int donc FIFO == 0
// EDF == 1
typedef enum e_sched
{
    FIFO,
    EDF,
}   t_sched;

long long ft_parsing(char *str);
int       ft_parsing_scheduler(char *str);
long long ft_atoi(char *str);


// creation d'une structure pour definir les programmeurs et leur dongles
// chaque dongles doit etre un pointeur d'une liste de dongles, car deux programmeurs
// vont devoir utiliser le meme dongle
typedef struct s_dongle
{
    int                 id;
    bool                is_used;
    pthread_mutex_t     mutex; // secu, verrou
    pthread_cond_t      cond; // gestion attente
    long long           last_used; // cooldown

} t_dongle;

typedef struct s_coder
{
    int          id;
    pthread_t    thread;
    t_dongle     *dongle1;
    t_dongle     *dongle2;
    long long    last_compil; // burnout/EDF
    int          nb_compil; // compteur de compilations
} t_coder;


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




#endif
