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
/* range un id dans le tas donne en parametre :
1. le place dans la premiere case libre (ids[size]), puis size++
2. le fait remonter tant qu'il est plus prioritaire que son parent
   (parent de i = (i - 1) / 2), en swappant a chaque etage
3. s'arrete quand il est au sommet (i == 0) ou a sa place (break)
le mutex et le ticket sont geres par l'appelant (scheduler) */
void	heap_push(t_heap *heap, t_data *data, int id)
{
	int	i;
	int	parent;

	i = heap->size;
	heap->ids[i] = id;
	heap->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (has_priority(data, heap->ids[parent], heap->ids[i]))
		{
			heap_swap(&heap->ids[i], &heap->ids[parent]);
			i = parent;
		}
		else
			break;
	}
}

/* fait redescendre le sommet du tas tant qu'il a un enfant :
- choisit le meilleur des deux enfants (2i+1 et 2i+2)
  (le 2e seulement s'il est dans le tas)
- si cet enfant est plus prioritaire, swap et on continue avec lui
- sinon il est a sa place : break */
void	heap_down(t_heap *heap, t_data *data)
{
	int	i;
	int	child1;
	int	child2;
	int	best;

	i = 0;
	while ((i * 2) + 1 < heap->size)
	{
		child1 = (i * 2) + 1;
		child2 = (i * 2) + 2;
		best = child1;
		if (child2 < heap->size
			&& has_priority(data, heap->ids[child1], heap->ids[child2]))
			best = child2;
		if (has_priority(data, heap->ids[i], heap->ids[best]))
		{
			heap_swap(&heap->ids[i], &heap->ids[best]);
			i = best;
		}
		else
			break;
	}
}

/* retire le sommet du tas donne : echange le sommet avec le dernier,
size--, puis fait redescendre le nouveau sommet a sa place.
le mutex est gere par l'appelant (scheduler) */
void	heap_pop(t_heap *heap, t_data *data)
{
	heap_swap(&heap->ids[0], &heap->ids[heap->size - 1]);
	heap->size--;
	heap_down(heap, data);
}
