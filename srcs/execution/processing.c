/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:23:29 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 23:23:32 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	everyinit(t_cub *cub, char *name)
{
	cub->fd = -1;
	cub->map_name = tdup(name);
	cub->map = malloc(sizeof(t_map));
	if (cub->map == NULL)
		wgas(cub, "fail malloc cub->map", NULL);
	cub->map->NO = NULL;
	cub->map->SO = NULL;
	cub->map->WE = NULL;
	cub->map->EA = NULL;
	cub->map->F = NULL;
	cub->map->C = NULL;
	cub->map->matrix = NULL;
	last_init(cub);
	parse_map(cub, name);
}

void	last_init(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (cub->data == NULL)
		wgas(cub, "fail malloc cub->data", NULL);
	cub->data->width = 0;
	cub->data->height = 0;
	cub->data->mlx = mlx_init();
	mlx_get_screen_size(cub->data->mlx, &cub->data->width, &cub->data->height);
	cub->data->win = mlx_new_window(cub->data->mlx, cub->data->width, cub->data->height, "CUB bcp de D");
	if (!cub->data->win)
	{
		free(cub->map);
		free(cub->data);
		free(cub->data->mlx);
		exit(2);
	}
	cub->data->img = mlx_new_image(cub->data->mlx, cub->data->width, cub->data->height);
	cub->data->addr = mlx_get_data_addr(cub->data->img,
			&cub->data->bits_per_pixel,
			&cub->data->line_length, &cub->data->endian);
	fill_win(cub);
}

void	fill_win(t_cub *cub)
{
	mlx_key_hook(cub->data->win, key_press, cub);
	mlx_hook(cub->data->win, 17, 0, &end_win, cub);
	mlx_loop(cub->data->mlx);
}



