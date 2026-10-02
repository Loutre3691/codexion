#include "codexion.h"

void    heap_swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
/* compare deux coder : selon si fifo ->  le premier arrive va en haut du tas
si edf -> celui avec la deadline la plus courte va en haut
a = parent b = enfant if comparaison between thise twice*/
bool    has_priority(t_data *data, int a, int b)
{
    bool    result;

    result = false;
    if(data->scheduler.enum_sched == FIFO)
        return (data->coder[a].ticket > data->coder[b].ticket);

    else if(data->scheduler.enum_sched == EDF)
    {

    }

    return result;
}
/* ajoute un coder dans le tas (file d'attente du scheduler) :
1. lui donne un ticket (son ordre d'arrivee, pour FIFO)
2. le place dans la premiere case libre (ids[size]), puis size++
3. le fait remonter tant qu'il est plus prioritaire que son parent
   (parent de i = (i - 1) / 2), en swappant a chaque etage
4. s'arrete quand il est au sommet (i == 0) ou a sa place (break)
le tout protege par mutex_counter car plusieurs threads y accedent */
void    heap_push(t_coder *coder, t_data *data)
{
    int i;
    int parent;

    pthread_mutex_lock(&data->scheduler.mutex_counter);
    i = data->scheduler.heap.size;
    coder->ticket = data->scheduler.ticket_counter;
    data->scheduler.ticket_counter++;

    data->scheduler.heap.ids[i] = coder->id;
    data->scheduler.heap.size++;

    while(i > 0)
    {
        parent = (i - 1) / 2;
        if(has_priority(data, data->scheduler.heap.ids[parent], data->scheduler.heap.ids[i]))
        {    
            heap_swap(&data->scheduler.heap.ids[i], &data->scheduler.heap.ids[parent]);
            i = parent;
        }
        else
            break;
    }
    pthread_mutex_unlock(&data->scheduler.mutex_counter);
}

/* retire le coder du sommet du tas (celui dont c'est le tour) :
1. echange le sommet avec le dernier, puis size-- (l'ancien sommet sort)
2. fait redescendre le nouveau sommet tant qu'il a un enfant :
   - choisit le meilleur des deux enfants (2i+1 et 2i+2)
     (le 2e seulement s'il est dans le tas)
   - si cet enfant est plus prioritaire, swap et on continue avec lui
   - sinon il est a sa place : break
le tout protege par mutex_counter */
void    heap_pop(t_data *data)
{
    int i;
    int child1;
    int child2;
    int best;

    pthread_mutex_lock(&data->scheduler.mutex_counter);
    i = 0;
    heap_swap(&data->scheduler.heap.ids[i], &data->scheduler.heap.ids[data->scheduler.heap.size - 1]);
    data->scheduler.heap.size--;
    while ((i * 2) + 1 < data->scheduler.heap.size)
    {
        child1 = (i * 2) + 1;
        child2 = (i * 2) + 2;
        best = child1;
        if(child2 < data->scheduler.heap.size && has_priority(data, data->scheduler.heap.ids[child1], data->scheduler.heap.ids[child2]))
            best = child2;
        if (has_priority(data, data->scheduler.heap.ids[i], data->scheduler.heap.ids[best]))
        {
            heap_swap(&data->scheduler.heap.ids[i], &data->scheduler.heap.ids[best]);
            i = best;
        }
        else
            break;
    }
    pthread_mutex_unlock(&data->scheduler.mutex_counter);
}
