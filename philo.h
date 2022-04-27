/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:17:42 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/26 21:11:25 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* includes */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

/* macros */
# define ERROR -1
# define RIGHT 0
# define LEFT 1
# define USLEEP 500

/* enums */
typedef enum e_states
{
	TAKEN_FIRST_FORK,
	TAKEN_SECOND_FORK,
	SLEEPING,
	THINKING,
	DIED
}	t_states;

/* structs */
typedef struct s_args
{
	int		nb_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_times;
}	t_args;

typedef struct s_body
{
	int				id;
	t_args			args;
	long			last_meal;
	long			fell_asleep;
	int				amount_of_meals;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	*print;
	pthread_mutex_t	*check_if_dead;
	pthread_mutex_t	*check_if_full;
	int				*full_stomachs;
}	t_body;

typedef struct s_phi
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	*check_if_dead;
	pthread_mutex_t	check_if_full;
	pthread_t		*threads;
	int				full_stomachs;
	t_args			args;
	t_body			*symposium;
}	t_phi;

/* prototypes */
int		enter_the_gate(int argc, char **argv, t_args *args);
int		init_mutex(t_phi *phi);
void	init_struct_philosoph(t_phi *phi, int philo_id);
int		grow_beards(t_phi *phi);
int		start_the_banquet(t_phi *phi);
long	get_current_time(void);
void	*same_procedure(void *philo_struct);
void	stop_the_banquet(t_phi *phi);
void	destroy_all_wisdom(t_phi *phi);
void	yousleep(int duration);

int		ft_atoi(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_itoa(int nbr);

void	print_output(pthread_mutex_t *mutex, int id, t_states state);
int		print_error(char *str);
void	print_input_instructions(void);

#endif
