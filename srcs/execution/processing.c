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
	mapInit(cub);
	dataInit(cub);
	cub->cam = malloc(sizeof(t_cam));
	if (!cub->cam)
		wgas(cub, "malloc cam failed", NULL);
	camInit(cub);
}

void	mapInit(t_cub *cub)
{
	cub->map = malloc(sizeof(t_map));
	if (cub->map == NULL)
		wgas(cub, "fail malloc cub->map", NULL);
	cub->map->l = 0;
	cub->map->L = 0;
	cub->map->NO = NULL;
	cub->map->SO = NULL;
	cub->map->WE = NULL;
	cub->map->EA = NULL;
	cub->map->F = NULL;
	cub->map->C = NULL;
	cub->map->matrix = NULL;
	cub->map->color_bsl = 0x757083;
	parse_map(cub, cub->map_name);
}

void	dataInit(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (cub->data == NULL)
		wgas(cub, "fail malloc cub->data", NULL);
	cub->data->width = 960;
	cub->data->height = 600;
	cub->data->width = cub->map->l * SPACE;
	cub->data->height = cub->map->L * SPACE;
	cub->data->mlx = mlx_init();
	// mlx_get_screen_size(cub->data->mlx, &cub->data->width, &cub->data->height);
	cub->data->x_off = cub->data->width / 2 - (cub->map->l / 2 * SPACE);
	cub->data->y_off = cub->data->height / 2 - (cub->map->L / 2 * SPACE);
	cub->data->win = mlx_new_window(cub->data->mlx, cub->data->width, cub->data->height, "CUB bcp de D");
	if (!cub->data->win)
	{
		free(cub->data->mlx);
		wgas(cub, "Couldn't open the window", NULL);
	}
	cub->data->img = mlx_new_image(cub->data->mlx, cub->data->width, cub->data->height);
	cub->data->addr = mlx_get_data_addr(cub->data->img,
			&cub->data->bits_per_pixel,
			&cub->data->line_length, &cub->data->endian);
}

void	camInit(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map->matrix[++y])
	{
		x = -1;
		while (cub->map->matrix[y][++x])
		{
			if (cub->map->matrix[y][x] == 'N' || cub->map->matrix[y][x] == 'S' || cub->map->matrix[y][x] == 'E' || cub->map->matrix[y][x] == 'O')
			{
				cub->cam->_2dPlayer = (t_mgam2i){x, y};
				cub->cam->player_pos = (t_mgam2f){(x * SPACE + cub->data->x_off), (y * SPACE + cub->data->y_off)};
				break ;
			}
		}
	}
	cub->cam->look = (t_mgam2f){cub->cam->player_pos.x + SPACE, cub->cam->player_pos.y + SPACE};
	cub->cam->oldlook = (t_mgam2f){0, 0};
	cub->cam->view_angle = 90 * M_PI / 180;
}