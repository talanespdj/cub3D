/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:23:29 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/21 17:31:53 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	mapinit(t_cub *cub, char *name)
{
	cub->map = malloc(sizeof(t_map));
	if (cub->map == NULL)
		wgas(cub, "fail malloc cub->map", NULL);
	cub->map->l = 0;
	cub->map->L = 0;
	cub->map->floor = NULL;
	cub->map->ceiling = NULL;
	cub->map->matrix = NULL;
	parse_map(cub, name);
}

void	datainit(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (cub->data == NULL)
		wgas(cub, "fail malloc cub->data", NULL);
	cub->data->width = 960;
	cub->data->height = 600;
	cub->data->mlx = mlx_init();
	mlx_get_screen_size(cub->data->mlx, &cub->data->width, &cub->data->height);
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

void	caminit(t_cub *cub)
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
				cub->map->matrix[y][x] = '0';
				cub->cam->player_pos = (t_mgam2f){x + 0.5, y + 0.5};
				break ;
			}
		}
	}
	cub->cam->look = (t_mgam2f){1.0, 0.0};
	mlx_mouse_move(cub->data->mlx, cub->data->win, cub->data->width / 2, cub->data->height / 2);
	mlx_mouse_get_pos(cub->data->mlx, cub->data->win, &cub->cam->mouse_x, &cub->cam->mouse_y);
}

void	rayinit(t_ray *ray)
{
	ray->x = 0;
	ray->map = (t_mgam2i){0, 0};
	ray->step = (t_mgam2i){-1, -1};
	ray->ray = (t_mgam2f){0.0, 0.0};
	ray->plane = (t_mgam2f){0.0, 0.66};
	ray->sidedist = (t_mgam2f){0.0, 0.0};
	ray->deltadist = (t_mgam2f){0.0, 0.0};
	ray->camerax = 0.0;
	ray->perpwalldist = 0.0;
	ray->whichside = 0;
}

void	txtinit(t_cub *cub)
{
	cub->txt[NO]->img = mlx_xpm_file_to_image(cub->data->mlx, cub->txt[NO]->name, &cub->txt[NO]->width, &cub->txt[NO]->height);
	if (!cub->txt[NO]->img)
		wgas(cub, "mlx_xpm_file_to_image", "north texture");
	cub->txt[SO]->img = mlx_xpm_file_to_image(cub->data->mlx, cub->txt[SO]->name, &cub->txt[SO]->width, &cub->txt[SO]->height);
	if (!cub->txt[SO]->img)
		wgas(cub, "mlx_xpm_file_to_image", "south texture");
	cub->txt[EA]->img = mlx_xpm_file_to_image(cub->data->mlx, cub->txt[EA]->name, &cub->txt[EA]->width, &cub->txt[EA]->height);
	if (!cub->txt[EA]->img)
		wgas(cub, "mlx_xpm_file_to_image", "east texture");
	cub->txt[WE]->img = mlx_xpm_file_to_image(cub->data->mlx, cub->txt[WE]->name, &cub->txt[WE]->width, &cub->txt[WE]->height);
	if (!cub->txt[WE]->img)
		wgas(cub, "mlx_xpm_file_to_image", "west texture");
}
