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
	if ((cub->map) && (cub->map->matrix))
		fsplit(cub->map->matrix);
	free(cub->map);
}

void	free_data(t_cub *cub)
{
	if (!cub->data)
		return ;
	if (cub->data->img)
		mlx_destroy_image(cub->data->mlx, cub->data->img);
	if (cub->data->win)
		mlx_destroy_window(cub->data->mlx, cub->data->win);
	if (cub->data->mlx)
	{
		mlx_destroy_display(cub->data->mlx);
		free(cub->data->mlx);
	}
	free(cub->data);
}

void	freend(t_cub *cub)
{
	int	i;

	i = -1;
	free_map(cub);
	if (cub->cam)
		free(cub->cam);
	if (cub->ray)
		free(cub->ray);
	while (++i < 4 && cub->txt[i])
	{
		if (cub->txt[i]->name)
			free(cub->txt[i]->name);
		if (cub->txt[i]->img)
			mlx_destroy_image(cub->data->mlx, cub->txt[i]->img);
		free(cub->txt[i]);
	}
	free_data(cub);
}
