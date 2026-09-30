#include "codexion.h"

/* etapes pour entrer dans le tas, attendre d'etre en haut du tas
prendre les dongles, sortir du tas */
void    scheduler(t_coder *coder)
{
//     t_scheduler *s;

//     s = &coder->data->scheduler;
    heap_push(coder);
    while(my_turn(coder) == false)
        usleep(100);
    dongle_used(coder);
    heap_pop(coder);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}
