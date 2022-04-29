/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrival.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:30:36 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/29 14:11:42 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_phi	*phi;

	phi = malloc(sizeof(t_phi));
	if (phi == NULL)
		return (print_error("malloc fail"));
	if (enter_the_gate(argc, argv, &phi->args) == ERROR)
	{
		print_input_instructions();
		return (1);
	}
	if (init_mutex(phi) == ERROR)
		return (ERROR);
	if (grow_beards(phi) == ERROR)
		return (ERROR);
	if (start_the_banquet(phi) == ERROR)
		return (ERROR);
	stop_the_banquet(phi);
	destroy_all_wisdom(phi);
	free(phi);
	return (0);
}
