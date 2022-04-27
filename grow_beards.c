/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_beards.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:45:05 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/19 18:30:24 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct_philosoph(t_phi *phi, int philo_id)
{
	phi->full_stomachs = 0;
	phi->symposium[philo_id].print = &phi->print;
	phi->symposium[philo_id].check_if_dead = &phi->check_if_dead[philo_id];
	phi->symposium[philo_id].check_if_full = &phi->check_if_full;
	phi->symposium[philo_id].full_stomachs = &phi->full_stomachs;
	phi->symposium[philo_id].args.must_eat_times = phi->args.must_eat_times;
	phi->symposium[philo_id].args.time_to_die = phi->args.time_to_die;
	phi->symposium[philo_id].args.time_to_eat = phi->args.time_to_eat;
	phi->symposium[philo_id].args.time_to_sleep = phi->args.time_to_sleep;
	phi->symposium[philo_id].id = philo_id;
	phi->symposium[philo_id].last_meal = 0;
	phi->symposium[philo_id].amount_of_meals = 0;
	phi->symposium[philo_id].fell_asleep = 0;
	phi->symposium[philo_id].forks[RIGHT] = &phi->forks[philo_id];
	// alternativ:
	// if ((philo_id + 1) == phi->args->nb_of_philos)
	// 	phi->symposium[philo_id].forks[LEFT] = 0;
	// else
	// 	phi->symposium[philo_id].forks[LEFT] = &phi->forks[philo_id + 1];
	phi->symposium[philo_id].forks[LEFT] = &phi->forks[(philo_id + 1)
		 % phi->args.nb_of_philos];
}

/* Allocating the philosophers bodies. */
int	grow_beards(t_phi *phi)
{
	int	i;

	phi->symposium = malloc(sizeof(t_body) * phi->args.nb_of_philos);
	if (!phi->symposium)
		return (print_error("malloc failed"));
	i = 0;
	while (i < phi->args.nb_of_philos)
	{
		init_struct_philosoph(phi, i);
		i++;
	}
	return (0);
}
