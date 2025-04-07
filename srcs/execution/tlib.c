/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:07:24 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 01:07:25 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

int	tstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*tdup(char *str)
{
	char	*dup;
	int		i;

	i = -1;
	dup = NULL;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (tstrlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str && str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*tjoin(char *str, char *add)
{
	char	*tjoin;
	int		i;
	int		r;

	i = -1;
	r = -1;
	if (!str)
		i = 0;
	if (!add)
		return (str);
	tjoin = malloc(sizeof(char) * (tstrlen(str) + (tstrlen(add) + 1)));
	if (!tjoin)
		return (NULL);
	while (str && str[++i])
		tjoin[i] = str[i];
	while (add[++r])
		tjoin[i + r] = add[r];
	tjoin[i + r] = '\0';
	free(str);
	return (tjoin);
}

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str && cmp && (str[++i] || cmp[i]))
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
	return (0);
}

void	length_map(t_cub *cub)
{
	char	*line;
	int		nill;

	cub->map->lar = 0;
	line = gnl(cub->fd);
	while (line)
	{
		nill = 0;
		while (line && null_linev2(line))
		{
			nill++;
			next_line(cub, &line);
			if (!null_linev2(line))
			{
				cub->map->lar += nill;
				break ;
			}
		}
		++cub->map->lar;
		if (tstrlen(line) > cub->map->lon)
			cub->map->lon = tstrlen(line);
		next_line(cub, &line);
	}
	cub->map->lon -= 1;
	free(line);
}
