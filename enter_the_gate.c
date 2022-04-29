/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_the_gate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:57:33 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/29 14:11:51 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Initialising the mutexes */
int	init_mutex(t_phi *phi)
{
	int	i;

	i = 0;
	phi->forks = malloc(sizeof(pthread_mutex_t) * phi->args.nb_of_philos);
	if (!phi->forks)
		return (print_error("malloc failed"));
	phi->check_if_dead = malloc(sizeof(pthread_mutex_t)
			* phi->args.nb_of_philos);
	if (!phi->check_if_dead)
		return (print_error("malloc failed"));
	while (i < phi->args.nb_of_philos)
	{
		if (pthread_mutex_init(&phi->forks[i], NULL) != 0)
			return (print_error("mutex couldn't be initialised"));
		if (pthread_mutex_init(&phi->check_if_dead[i], NULL) != 0)
			return (print_error("mutex couldn't be initialised"));
		i++;
	}
	if (pthread_mutex_init(&phi->print, NULL) != 0)
		return (print_error("mutex couldn't be initialised"));
	if (pthread_mutex_init(&phi->check_if_full, NULL) != 0)
		return (print_error("mutex couldn't be initialised"));
	return (0);
}

static void	init_args(t_args *args)
{
	args->must_eat_times = -1;
	args->nb_of_philos = 0;
	args->time_to_die = 0;
	args->time_to_eat = 0;
	args->time_to_sleep = 0;
}

/* Checks if input is correct and converts it */
int	enter_the_gate(int argc, char **argv, t_args *args)
{
	init_args(args);
	if (argc < 5 || argc > 6)
		return (print_error("wrong number of arguments"));
	if (argc == 6)
		args->must_eat_times = ft_atoi(argv[5]);
	args->nb_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (!args->must_eat_times || !args->nb_of_philos || !args->time_to_die
		|| !args->time_to_eat || !args->time_to_sleep)
		return (print_error("incorrect argument"));
	return (0);
}
