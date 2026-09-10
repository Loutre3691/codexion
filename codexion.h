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

typedef struct s_monitor t_monitor; // déclaration anticipée : "t_monitor existe, promis"

/* creation d'une structure pour definir les programmeurs et leur dongles
 chaque dongles doit etre un pointeur d'une liste de dongles, car deux programmeurs
 vont devoir utiliser le meme dongle */
typedef struct s_dongle
{
    int                 id;
    bool                is_used;
    pthread_mutex_t     mutex; // secu, verrou
    pthread_cond_t      cond; // gestion attente, reveil un thread qui attend
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
    t_monitor    *monitor;
} t_coder;

typedef struct s_monitor
{
    bool                stop_routine; // LA CONDITION (la vraie donnée, le booléen)
    pthread_mutex_t     stop_mutex;   // LE VERROU (protège l'accès à stop_routine)
    pthread_cond_t      stop_cond; // LA SONNETTE (le mécanisme qui réveille les threads)
    long long           start_time; // time du debut pour le timer au fur et a mesure
    pthread_mutex_t     print_mutex; // permet de mettre un mutex sur les printf 
    t_data              *data;     // acces en lecture des arguments
    t_coder             *coder; // accès en lecture à l'état de chaque coder
} t_monitor;



// FONCTIONS
long long           ft_parsing(char *str);
int                 ft_parsing_scheduler(char *str);
long long           ft_parsing_nbr_coders(char *str);
long long           ft_atoi(char *str);
void                simulator(t_data *data);
void                *routine_function(void *arg);
void                init_monitor(t_monitor *monitor, t_data *data, t_coder *coders);
void                create_coders(t_data *data, t_dongle *dongles, t_coder *coders, t_monitor *monitor);
void                init_dongle(t_dongle *dongles, t_data *data);
void                destroy_dongles(t_data *data, t_dongle *dongles);
void                join_coders(t_data *data, t_coder *coders);
long long           edf(t_coder *coder);
long long           fifo(t_coder *coder);
void                dongle_used(t_coder *coder);
void                left_dongle_used(t_coder *coder);
void                right_dongle_used(t_coder *coder);
void                ft_compile(t_coder *coder);
void                ft_debug(t_coder *coder);
void                ft_refactoring(t_coder *coder);
long long           get_time_ms();
struct timespec     get_time_s(long long *deadline);
void                free_all(t_coder *coders, t_dongle *dongles, t_monitor *monitor);

#endif
