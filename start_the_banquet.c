/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_banquet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:11:25 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/29 14:11:30 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	timing;
	static long		big_bang = 0;

	gettimeofday(&timing, NULL);
	if (big_bang == 0)
	{
		big_bang = (timing.tv_sec * 1000) + (timing.tv_usec / 1000);
		return (0);
	}
	return ((timing.tv_sec * 1000) + (timing.tv_usec / 1000) - big_bang);
}

void	yousleep(useconds_t duration)
{
	long			start;
	long			now;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	now = start;
	while (now - start < duration)
	{
		usleep(USLEEP);
		gettimeofday(&tv, NULL);
		now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}

/* Allocating and creating one thread per philo.
   The threads get detached right afterwards. */
int	start_the_banquet(t_phi *phi)
{
	int	i;

	i = 0;
	phi->threads = malloc(sizeof(pthread_t) * phi->args.nb_of_philos);
	if (phi->threads == NULL)
		return (print_error("malloc failed"));
	while (i < phi->args.nb_of_philos)
	{
		if (pthread_create(&phi->threads[i], NULL, &same_procedure,
				&phi->symposium[i]) != 0)
			return (print_error("thread couldn't be created"));
		if (pthread_detach(phi->threads[i]) != 0)
			return (print_error("thread couldn't be detached"));
		i++;
	}
	return (0);
}
