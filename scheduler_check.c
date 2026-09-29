#include "codexion.h"

/* permet de gerer le scheduler  */
void    scheduler_check(t_coder *coder)
{
    if (coder->data->scheduler.enum_sched == FIFO)
    {
        add_fifo(coder); // ajoute a la liste fifo
        while(check_fifo(coder) == false)
            usleep(100);
        dongle_used(coder); // utilie ses dongles si premier de la liste
        remove_first_fifo(coder); // se retire de la liste
    }
    else
    {
        add_edf(coder); //ajoute a la liste edf 
        check_edf(coder);
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
}
