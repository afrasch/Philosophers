/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:24:42 by afrasch           #+#    #+#             */
/*   Updated: 2022/04/29 14:12:22 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns the length of str.*/
static size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/* Searches for the first occurrence of (typecasted char) c in str.
   Returns a pointer to it. */
char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	size_t	l;

	if (!str)
		return (NULL);
	i = 0;
	l = ft_strlen((char *)str);
	while (i <= l)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		else
			i++;
	}
	return (NULL);
}

/* Allocates and duplicates str. Returns a pointer to the new string */
static char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	i = ft_strlen((char *)str);
	dest = (char *)malloc(i + 1);
	if (dest == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* Counts the digits of a number in base 10. */
static int	ft_digit_count(int nbr)
{
	int	digits;

	digits = 0;
	if (nbr <= 0)
		digits++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		digits++;
	}
	return (digits);
}

/* Allocates and returns a string representing the integer received as an
   argument. Returns NULL if allocation fails. */
char	*ft_itoa(int nbr)
{
	char	*result;
	int		digits;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = ft_digit_count(nbr);
	result = (char *)malloc(digits + 1);
	if (!result)
		return (0);
	result[digits] = '\0';
	if (nbr < 0)
		result[0] = '-';
	else if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		--digits;
		if (nbr < 0)
			nbr *= -1;
		result[digits] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (result);
}
