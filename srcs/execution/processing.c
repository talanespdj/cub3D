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
	cub->ray = malloc(sizeof(t_ray));
	if (!cub->ray)
		wgas(cub, "malloc ray failed", NULL);
	rayInit(cub->ray);
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
	// 0x757083;
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
	int	y;

	y = -1;
	while (cub->map->matrix[++y])
		if (setLook(cub, cub->map->matrix[y], y))
			return ;
	wgas(cub, "pblm ya pas de pos de joueur dans la map", NULL);
}

int	setLook(t_cub *cub, char *str, int y)
{
	int	x;

	x = -1;
	while (str[++x])
	{
		if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'O')
		{
			if (str[x] == 'N')
				cub->cam->look = (t_mgam2f){0, 1};
			else if (str[x] == 'S')
				cub->cam->look = (t_mgam2f){0, -1};
			else if (str[x] == 'E')
				cub->cam->look = (t_mgam2f){-1, 0};
			else if (str[x] == 'O')
				cub->cam->look = (t_mgam2f){1, 0};
			cub->cam->player_pos = (t_mgam2f){x + 1, y + 1};
			return (1);
		}
	}
	return (0);
}

void	rayInit(t_ray *ray)
{
	ray->map = (t_mgam2i){0, 0};
	ray->step = (t_mgam2i){0, 0};
	ray->ray = (t_mgam2f){0.0, 0.0};
	ray->plane = (t_mgam2f){0.0, 0.66};
	ray->sideDist = (t_mgam2f){0.0, 0.0};
	ray->deltaDist = (t_mgam2f){0.0, 0.0};
	ray->cameraX = 0.0;
	ray->perpWallDist = 0.0;
	ray->whichSide = 0;
}