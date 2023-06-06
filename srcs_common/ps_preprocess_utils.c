/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_preprocess_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:51:02 by marvin            #+#    #+#             */
/*   Updated: 2023/06/06 18:27:56 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	ps_valid_char(char c)
{
	if (ft_isspace(c) || ft_isdigit(c) || c == '+' || c == '-')
		return (1);
	return (0);
}

int	wordnum(char *str)
{
	int	count;
	int	i;
	int	has_digits;

	i = 0;
	count = 0;
	has_digits = 0;
	if (str[i] && !ft_isspace(str[i]))
		count++;
	while (str[i] && !ft_isspace(str[i]) && ps_valid_char(str[i]))
	{
		if (ft_isdigit(str[i]))
			has_digits = 1;
		i++;
	}
	while (str[i] && ps_valid_char(str[i]))
	{
		if (!ft_isspace(str[i]) && ft_isspace(str[i - 1]))
			count++;
		if (ft_isdigit(str[i]))
			has_digits = 1;
		i++;
	}
	if ((str[i] && !ps_valid_char(str[i])) || !has_digits)
		return (0);
	return (count);
}

int	ps_atoi_overf(int res, char next, int *sign)
{
	int	max;

	max = INT_MAX / 10;
	if (res < max)
		return (1);
	if (res > max)
	{
		*sign = 0;
		return (0);
	}
	else if (res == max)
	{
		if (*sign == 1 && next > INT_MAX % 10 + '0')
		{
			*sign = 0;
			return (0);
		}
		if (*sign == -1 && next > -(INT_MIN % 10) + '0')
		{
			*sign = 0;
			return (0);
		}
	}
	return (1);
}

int	ps_atoiable(char **arg, int *placenum)
{
	int		res;
	int		sign;
	char	*str;

	str = *arg;
	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str && *str == '-')
		sign = -1;
	if (*str && (*str == '-' || *str == '+'))
		str++;
	if (!ft_isdigit(*str))
		sign = 0;
	res = 0;
	while (*str && ft_isdigit(*str) && ps_atoi_overf(res, *str, &sign))
		res = res * 10 - '0' + *str++;
	*placenum = res * sign;
	if (sign == 0 || (!ft_isspace(*str) && *str))
		return (0);
	*arg = str;
	return (1);
}
