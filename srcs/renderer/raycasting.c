/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:51:37 by tespandj          #+#    #+#             */
/*   Updated: 2024/12/01 01:03:59 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"


void	lengthRay(t_cub *cub)
{
	while (1)
	{
		if (cub->cam->sideDist.x < cub->cam->sideDist.y)
		{
			cub->cam->sideDist.x += cub->cam->deltaDist.x
			cub->cam->map.x += step.x;
			side = 0;
		}
		else
		{
			cub->cam->sideDist.y += cub->cam->deltaDist.y
			cub->cam->map.y += step.y;
			side = 1;
		}
		if (cub->map->matrix[cub->cam->map.y][cub->cam->map.x] > 0)
			break ;
	}
	if (side == 0)
		cub->cam-

}






void	raycast(t_cub *cub)
{
	t_mgam2i	pos;
	t_mgam2i	view;
	int		x;
	t_mgam2i	map;
	int		stepx;
	int		stepy;
	double		cameraX;
	double		perpWallDist;

	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player / 2), cub->cam->player_pos.y + (ratio_player / 2)};
	view = (t_mgam2i){pos.x + cub->cam->look.x, pos.y + cub->cam->look.y}; // temporaire

	x = -1;
	stepx = -1;
	stepy = -1;
	map.x = (int)cub->cam->player_pos.x;
	map.y = (int)cub->cam->player_pos.y;
	while (++x < cub->data->width)
	{
		cameraX = 2 * x / (double)cub->data->width - 1;
		cub->cam->ray.x = cub->cam->look.x + (cub->cam->plane.x * cameraX);
		cub->cam->ray.y = cub->cam->look.y + (cub->cam->plane.x * cameraX);
		cub->cam->deltaDist.x = fabs(1 / cub->cam->ray.x);
		cub->cam->deltaDist.y = fabs(1 / cub->cam->ray.y);
		
		if (cub->cam->ray.x > 0)
		{
			stepx = 1;
			cub->cam->sideDist.x = (map.x + 1.0 - cub->cam->player_pos.x) * cub->cam->deltaDist.x;
		}
		else
			cub->cam->sideDist.x = (cub->cam->player_pos.x - map.x) * cub->cam->deltaDist.x;
		if (cub->cam->ray.y > 0)
		{
			stepy = 1;
			cub->cam->sideDist.y = (map.y + 1.0 - cub->cam->player_pos.y) * cub->cam->deltaDist.y;
		}
		else
			cub->cam->sideDist.y = (cub->cam->player_pos.y - map.y) * cub->cam->deltaDist.y;
		lengthRay(cub);
		
					


		
	}
	// dda(cub, pos, view);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

int	wallHit(t_cub *cub, int x, int y)
{
	x = (x - cub->data->x_off) / SPACE;
	y = (y - cub->data->y_off) / SPACE;
	if ((x < 0 || x > cub->map->l) || (y < 0 || y > cub->map->L))
		return (1);
	if (cub->map->matrix[y][x] == '1')
		return (1);
	return 0;
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char *dst;
	if ((x < data->width && x > 0) && (y < data->height && y > 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	// else
	// 	printf("Bouffon t'ecris en dehors\n");
}

