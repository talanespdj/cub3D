/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:05:10 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/21 03:03:39 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	next_line(t_cub *cub, char **line)
{
	free(*line);
	*line = gnl(cub->fd);
}

void	wgas(t_cub *cub, char *arg, char *str)
{
	printf("Error\n");
	if (arg)
		printf("%s", arg);
	if (str)
		printf(": %s", str);
	printf("\n");
	freend(cub);
	if (cub->fd > 0)
		close(cub->fd);
	exit(1);
}

void	wegotasplituation(struct spt x)
{
	int	i;

	i = -1 ;
	while (x.split[++i] && i <= x.op)
		free(x.split[i]);
	free(x.split);
}

void	free_map(t_cub *cub)
{
	if (cub->map)
		if (cub->map->matrix)
			fsplit(cub->map->matrix);
	if (cub->fd > 0)
		gnl_free(cub->fd);
	free(cub->map);
}

void	freend(t_cub *cub)
{
	free_map(cub);
	if (cub->data)
		free(cub->data);
	if (cub->cam)
		free(cub->cam);
	if (cub->ray)
		free(cub->ray);
}
