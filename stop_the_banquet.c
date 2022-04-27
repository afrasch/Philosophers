/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_the_banquet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:36:49 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/19 18:24:19 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_wisdom(t_phi *phi)
{
	int	i;

	i = 0;
	while (i < phi->args.nb_of_philos)
	{
		pthread_mutex_destroy(&phi->forks[i]);
		pthread_mutex_destroy(&phi->check_if_dead[i]);
		i++;
	}
	pthread_mutex_destroy(&phi->print);
	pthread_mutex_destroy(&phi->check_if_full);
	free(phi->forks);
	free(phi->check_if_dead);
	free(phi->threads);
	free(phi->symposium);
}

bool	poke_the_dead(t_phi *phi)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&phi->print);
	while (i < phi->args.nb_of_philos)
	{
		pthread_mutex_lock(&phi->check_if_dead[i]);
		if ((get_current_time() - phi->symposium[i].last_meal)
			>= phi->args.time_to_die)
		{
			// phi->symposium[i].dead = -1;//als message: simulation beendet
			// // in routine abfragen und jeden einzeln beenden ( wie mit pthread_join)
			pthread_mutex_unlock(&phi->check_if_dead[i]);
			print_output(&phi->print, i, DIED);
			return (true);
		}
		pthread_mutex_unlock(&phi->check_if_dead[i]);
		i++;
	}
	pthread_mutex_unlock(&phi->print);
	return (false);
}

bool	poke_the_stomach(t_phi *phi)
{
	pthread_mutex_lock(&phi->check_if_full);
	if (phi->full_stomachs == phi->args.nb_of_philos)
	{
		pthread_mutex_unlock(&phi->check_if_full);
		return (true);
	}
	pthread_mutex_unlock(&phi->check_if_full);
	return (false);
}

/* Check if a philo is done with eating or died. */
void	stop_the_banquet(t_phi *phi)
{
	while (43)
	{
		if (poke_the_dead(phi) == true)
			break ;
		if (poke_the_stomach(phi) == true)
			break ;
		usleep(100);
	}
}
