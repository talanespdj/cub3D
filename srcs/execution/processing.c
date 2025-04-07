/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 23:23:29 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 16:03:51 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	mapinit(t_cub *cub, char *name)
{
	int	i;

	i = -1;
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		wgas(cub, "fail malloc cub->map", NULL);
	cub->map->lon = 0;
	cub->map->lar = 0;
	cub->map->floor = 0;
	cub->map->ceiling = 0;
	cub->map->matrix = NULL;
	while (++i < 4)
		cub->txt[i] = NULL;
	if (access(name, F_OK))
		wgas(cub, name, "File doesn't exist");
	else if (access(name, R_OK))
		wgas(cub, name, "No permission to read the map");
	cub->fd = open(name, O_RDONLY);
	if (cub->fd == -1)
		wgas(cub, name, "Failed to open the map");
	parse_map(cub, name);
}

void	datainit(t_cub *cub)
{
	cub->data = malloc(sizeof(t_data));
	if (!cub->data)
		wgas(cub, "fail malloc cub->data", NULL);
	cub->data->mlx = NULL;
	cub->data->win = NULL;
	cub->data->img = NULL;
	cub->data->addr = NULL;
	cub->data->width = 960;
	cub->data->height = 600;
	cub->data->mlx = mlx_init();
	if (!cub->data->mlx)
		wgas(cub, "fail mlx open", NULL);
	mlx_get_screen_size(cub->data->mlx, &cub->data->width, &cub->data->height);
	cub->data->win = mlx_new_window(cub->data->mlx, cub->data->width,
			cub->data->height, "CUB bcp de D");
	if (!cub->data->win)
		wgas(cub, "Couldn't open the window", NULL);
	cub->data->img = mlx_new_image(cub->data->mlx, cub->data->width,
			cub->data->height);
	if (!cub->data->img)
		wgas(cub, "mlx_new_image failed", NULL);
	cub->data->addr = mlx_get_data_addr(cub->data->img, &cub->data->bppixel,
			&cub->data->line_length, &cub->data->endian);
	if (!cub->data->addr)
		wgas(cub, "mlx_get_data_addr failed", NULL);
}

void	caminit(t_cub *cub)
{
	char	**matrix;
	int		x;
	int		y;

	y = -1;
	matrix = cub->map->matrix;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (matrix[y][x] == 'N' || matrix[y][x] == 'S' ||
				matrix[y][x] == 'E' || matrix[y][x] == 'W')
			{
				setlook(cub, matrix[y][x]);
				cub->cam->player_pos = (t_mgam2f){x + 0.5, y + 0.5};
				matrix[y][x] = '0';
				break ;
			}
		}
		if (matrix[y][x])
			break ;
	}
	if (!matrix[y])
		wgas(cub, "No player pos detected", NULL);
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
	t_txt	*tmp;
	int		i;

	i = -1;
	while (++i < 4)
	{
		tmp = cub->txt[i];
		tmp->img = mlx_xpm_file_to_image(cub->data->mlx,
				tmp->name, &tmp->width, &tmp->height);
		if (!tmp->img)
			wgas(cub, "textures", "mlx_xpm_file_to_image");
		tmp->addr = mlx_get_data_addr(tmp->img, &tmp->bits_per_pixel,
				&tmp->size_line, &tmp->endian);
		if (!tmp->addr)
			wgas(cub, "textures", "get_data_addr");
	}
}
