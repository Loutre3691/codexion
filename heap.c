#include "codexion.h"

/* compare selon si fifo deux coder  le premier arrive va en hau du tas
si edf celui avec la deadline la plus courte va en haut*/
bool    has_priority(t_data *data, int a, int b)
{
    bool    result;

    result = true;
    if(data->scheduler.enum_sched == FIFO)
        return (data->coder[a].ticket < data->coder[b].ticket);

    else if(data->scheduler.enum_sched == EDF)
    {

    }

    return result;
}
void    heap_push(t_coder *coder, t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_lock(&coder->data->scheduler.mutex_counter);
    coder->ticket = coder->data->scheduler.ticket_counter;
    coder->data->scheduler.ticket_counter++;

    has_priority(data, i, i + 1);
    
        
    
    pthread_mutex_unlock(&coder->data->scheduler.mutex_counter);


}


// void    heap_pop(t_coder *coder)
// {



// }