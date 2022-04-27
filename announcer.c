/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announcer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:13:46 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/18 13:50:14 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_error(char *str)
{
	if (str)
		printf("Error: %s\n", str);
	else
		printf("Error\n");
	return (ERROR);
}

void	print_input_instructions(void)
{
	printf("The arguments should look as follows:\n");
	printf("./philo [1] [2] [3] [4] [5] (integers above zero)\n");
	printf("[1] number_of_philosophers\n");
	printf("[2] time_to_die in ms\n");
	printf("[3] time_to_eat in ms\n");
	printf("[4] time_to_sleep in ms\n");
	printf("[5] number_of_times_each_philosopher_must_eat (optional)\n");
}

void	print_output(pthread_mutex_t *mutex, int id, t_states state)
{
	id++;
	if (state != DIED)//bewirkt manchmal meldung bei  ./philo 4 410 200 200 ??
	{
		if (pthread_mutex_lock(mutex) != 0)
			return ;
	}
	if (state == TAKEN_FIRST_FORK || state == TAKEN_SECOND_FORK)
		printf("%ld %d has taken a fork\n", get_current_time(), id);
	if (state == TAKEN_SECOND_FORK)
		printf("%ld %d is eating\n", get_current_time(), id);
	else if (state == SLEEPING)
		printf("%ld %d is sleeping\n", get_current_time(), id);
	else if (state == THINKING)
		printf("%ld %d is thinking\n", get_current_time(), id);
	else if (state == DIED)
		printf("%ld %d has died\n", get_current_time(), id);
	if (state != DIED)
		pthread_mutex_unlock(mutex);
}
