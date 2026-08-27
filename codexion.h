#ifndef CODEXION_H
# define CODEXION_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>


long long ft_parsing(char *str);
long long ft_parsing_schuelder(char *str);
long long ft_atoi(char *str);


// creation d'une structure pour definir les programmeurs et leur dongles
// chaque dongles doit etre un pointeur d'uneliste de dongles, car deux programmeurs
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




#endif
