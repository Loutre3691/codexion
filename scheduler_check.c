#include "codexion.h"

#include "codexion.h"

/* vrai si le coder est au sommet de la file de SES DEUX dongles */
bool	my_turn(t_coder *coder)
{
	bool	result;

	pthread_mutex_lock(&coder->data->scheduler.mutex_counter);
	result = (coder->left_dongle->heap.ids[0] == coder->id
			&& coder->right_dongle->heap.ids[0] == coder->id);
	pthread_mutex_unlock(&coder->data->scheduler.mutex_counter);
	return (result);
}

/* 1. prend UN ticket et s'inscrit dans la file des deux dongles
2. attend d'etre au sommet des deux files
3. prend les dongles, puis sort des deux files */
void	scheduler(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&data->scheduler.mutex_counter);
	coder->ticket = data->scheduler.ticket_counter;
	data->scheduler.ticket_counter++;
	heap_push(&coder->left_dongle->heap, data, coder->id);
	heap_push(&coder->right_dongle->heap, data, coder->id);
	pthread_mutex_unlock(&data->scheduler.mutex_counter);
	while (my_turn(coder) == false)
		usleep(100);
	dongle_used(coder);
	pthread_mutex_lock(&data->scheduler.mutex_counter);
	heap_pop(&coder->left_dongle->heap, data);
	heap_pop(&coder->right_dongle->heap, data);
	pthread_mutex_unlock(&data->scheduler.mutex_counter);
}
