/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:23:44 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/27 16:58:14 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Compares str1 and str2. Returns 0 if they are identical or the amount of
   different chars (>0 if str1 more, <0 if str2 is more). */
static int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != 0 && str1[i] == str2[i])
		i++;
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}

/* Checks for: empty string, correct chars as input, prefix only at the
   beginning, if there is only one prefix, if sign exists. */
static int	ft_atoi_inputcheck(const char *str)
{
	int	i;
	int	prefix;

	i = 0;
	prefix = 0;
	while (str && str[i])
	{
		if (ft_strchr("0123456789+", str[i]) == 0)
			break ;
		if (str[i] == '+')
		{
			prefix++;
			if (i > 0)
				return (ERROR);
		}
		i++;
	}
	if (prefix > 1 || str[i] != '\0' || !str)
		return (ERROR);
	return (0);
}

/* Checks if atoi did the right job by converting its output back to a string
   and comparing the result with the original string */
static int	ft_is_int(const char *str, int input)
{
	char	*temp;

	temp = ft_itoa(input);
	if (str[0] == '+')
		str = str + 1;
	if (!ft_strcmp(temp, str))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

/* Turns ascii into an integer. Skips spaces, checks and puts sign,
   then transfers to int. Returns the int or 0 if it failed. */
int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	*error;

	result = 0;
	i = 0;
	error = NULL;
	if (str[i] == '-' || ft_atoi_inputcheck(str) == ERROR)
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] > 47 && str[i] < 58)
		result = result * 10 + str[i++] - 48;
	if (ft_is_int(str, result) == 1)
		return (result);
	return (0);
}
