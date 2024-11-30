/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 02:17:13 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/30 02:17:14 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

long long int	atolli(char *str)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nt = nt * 10 + (str[i] - 48);
		i++;
	}
	return (nt *= sign);
}

int	valid_lli(long long int nt, char c, int sign, int situation)
{
	if (situation == 1)
		if (sign > 0 && ((nt > (LLONG_MAX - (c - 48)) / 10)
				|| (nt == (LLONG_MAX - (c - 48)) / 10
					&& c - 48 > LLONG_MAX % 10)))
			return (0);
	if (situation == 2)
		if (sign < 0 && ((nt > (LLONG_MIN + (c - 48)) / (-10))
				|| (nt == (LLONG_MIN + (c - 48)) / (-10)
					&& c - 48 > LLONG_MIN % 10 * (-1))))
			return (0);
	return (1);
}

int	check_lli(char *str)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!valid_lli(nt, str[i], sign, 1))
			return (0);
		if (!valid_lli(nt, str[i], sign, 2))
			return (0);
		nt = nt * 10 + (str[i] - 48);
		i++;
	}
	if (str[i])
		return (0);
	return (1);
}
