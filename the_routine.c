/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:11:08 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/29 14:11:20 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_involved(t_body *philo)
{
	pthread_mutex_lock(philo->forks[philo->id % 2]);
	print_output(philo->print, philo->id, TAKEN_FIRST_FORK);
	if (philo->id % 2 == 0)
		usleep(USLEEP);
	pthread_mutex_lock(philo->forks[(philo->id + 1) % 2]);
	print_output(philo->print, philo->id, TAKEN_SECOND_FORK);
}

static int	count_meals(t_body *philo)
{
	pthread_mutex_lock(philo->check_if_dead);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->check_if_dead);
	philo->amount_of_meals++;
	if (philo->amount_of_meals == philo->args.must_eat_times)
	{
		pthread_mutex_lock(philo->check_if_full);
		(*philo->full_stomachs)++;
		pthread_mutex_unlock(philo->check_if_full);
		if (philo->amount_of_meals >= philo->args.must_eat_times)
			return (ENOUGH);
	}
	return (0);
}

static void	fall_asleep(t_body *philo)
{
	yousleep(philo->args.time_to_eat);
	print_output(philo->print, philo->id, SLEEPING);
}

static void	time_to_think_about_stuff(t_body *philo)
{
	yousleep(philo->args.time_to_sleep);
	print_output(philo->print, philo->id, THINKING);
}

/* The routine for each thread. */
void	*same_procedure(void *philo_struct)
{
	t_body	*philo;
	int		meals;

	meals = 0;
	philo = philo_struct;
	if (philo->id % 2 == 1)
		yousleep(philo->args.time_to_eat);
	while (43)
	{
		get_involved(philo);
		if (count_meals(philo) == ENOUGH)
		{
			pthread_mutex_unlock(philo->forks[philo->id % 2]);
			pthread_mutex_unlock(philo->forks[(philo->id + 1) % 2]);
			break ;
		}
		fall_asleep(philo);
		pthread_mutex_unlock(philo->forks[philo->id % 2]);
		pthread_mutex_unlock(philo->forks[(philo->id + 1) % 2]);
		time_to_think_about_stuff(philo);
	}
	return (NULL);
}
