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
typedef struct s_coder t_coder;
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

/* creation d'un enum  pour le schuelder avec fifo et edf pour
le  8eme argument, enum valeur = int donc FIFO == 0
EDF == 1 */
typedef enum e_sched
{
    FIFO,
    EDF,
} t_sched;

/* tas(priotiry queue): le + proritaire est toujours en ids[0]*/
typedef struct s_heap
{
    int     *ids;
    int     size;
} t_heap;

/* strcuture cree pour regrouper les list fifo edf et le enum_sched*/
typedef struct s_scheduler
{
    t_sched             enum_sched;
    t_heap              heap;
    long long           ticket_counter;
    pthread_mutex_t     mutex_counter;
} t_scheduler;

typedef struct s_data
{
    long long       number_of_coders;
    long long       time_to_burnout;
    long long       time_to_compile;
    long long       time_to_debug;
    long long       time_to_refactor;
    long long       number_of_compile_required;
    long long       cooldown;
    t_scheduler     scheduler;
    t_coder         *coder;
    t_monitor       *monitor;
    t_dongle        *dongle;
} t_data;

typedef struct s_coder
{
    int                 id;
    pthread_t           thread;
    t_data              *data; // pointeur vers ma struct data
    t_dongle            *right_dongle;
    t_dongle            *left_dongle;
    long long           last_compil; // burnout/EDF
    int                 nb_compil; // compteur de compilations
    t_monitor           *monitor;
    pthread_mutex_t     mutex_last_compil;
    long long           ticket; // ordre arrive pour fifo
} t_coder;

typedef struct s_monitor
{
    bool                stop_routine; // LA CONDITION (la vraie donnée, le booléen)
    long long           start_time; // time du debut pour le timer au fur et a mesure
    long long           deadline_burnout; // le temps ou ca burnout
    pthread_t           thread;
    pthread_mutex_t     stop_mutex; // LE VERROU (protège l'accès à stop_routine)
    pthread_cond_t      stop_cond; // LA SONNETTE (le mécanisme qui réveille les threads)
    pthread_mutex_t     print_mutex; // permet de mettre un mutex sur les printf 
    t_data              *data;     // acces en lecture des arguments
    t_coder             *coder; // accès en lecture à l'état de chaque coder
} t_monitor;


//                               FONCTIONS

// Parsing
void                sort_parsing(int arg, int argc, char **argv, t_data *data);
long long           ft_parsing(char *str);
int                 ft_parsing_scheduler(char *str);
long long           ft_parsing_nbr_coders(char *str);
long long           ft_atoi(char *str);

// Init
void                init_t_monitor(t_monitor *monitor, t_data *data, t_coder *coder);
void                init_t_coder(t_data *data, t_dongle *dongle, t_coder *coder, t_monitor *monitor);
void                init_t_dongle(t_dongle *dongle, t_data *data);
void                init_scheduler(t_data *data);

// Begin
void                simulator(t_data *data);
void                ft_malloc_data(t_data *data);
void                join_coder(t_data *data, t_coder *coder);

// Dongle
void                dongle_used(t_coder *coder);
void                left_dongle_used(t_coder *coder);
void                right_dongle_used(t_coder *coder);
void                put_down_dongles(t_coder *coder);

// Routine
void                *routine_function(void *arg);
void                ft_compile(t_coder *coder);
void                ft_debug(t_coder *coder);
void                ft_refactoring(t_coder *coder);

// Time
long long           get_time_ms();
struct timespec     get_time_s(long long *deadline);

// Monitor
void                *monitor_routine(void *arg);
bool                ft_print_burnout(t_monitor *monitor, int i);
bool	            all_coders_done(t_monitor *monitor);


// Scheduler
void                scheduler(t_coder *coder);
void                heap_push(t_coder *coder, t_data *data)
bool                has_priority(t_data *data, int a, int b);
void                heap_pop(t_coder *coder);



// Cleaning
void                free_all(t_coder *coder, t_dongle *dongle, t_monitor *monitor, t_data * data);
void                destroy_mutex(t_data *data, t_dongle *dongle, t_coder *coder);

#endif
