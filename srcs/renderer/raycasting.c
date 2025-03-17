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

void	raycast(t_cub *cub)
{
	int		x;
	double		cameraX;

	x = -1;
	while (++x < cub->data->width)
	{
		cameraX = 2 * x / (double)cub->data->width - 1;
		cub->ray->ray = (t_mgam2f){cub->cam->look.x + (cub->ray->plane.x * cameraX),
						cub->cam->look.y + (cub->ray->plane.y * cameraX)};
		cub->ray->map = (t_mgam2i){(int)cub->cam->player_pos.x, (int)cub->cam->player_pos.y};
		cub->ray->deltaDist = (t_mgam2f){fabs(1 / cub->ray->ray.x), fabs(1 / cub->ray->ray.y)};
		if (cub->ray->ray.x > 0)
		{
			cub->ray->step.x = 1;
			cub->ray->sideDist.x = (cub->ray->map.x + 1.0 - cub->cam->player_pos.x) * cub->ray->deltaDist.x;
		}
		else
			cub->ray->sideDist.x = (cub->cam->player_pos.x - cub->ray->map.x) * cub->ray->deltaDist.x;
		if (cub->ray->ray.y > 0)
		{
			cub->ray->step.y = 1;
			cub->ray->sideDist.y = (cub->ray->map.y + 1.0 - cub->cam->player_pos.y) * cub->ray->deltaDist.y;
		}
		else
			cub->ray->sideDist.y = (cub->cam->player_pos.y - cub->ray->map.y) * cub->ray->deltaDist.y;
		lengthRay(cub, cub->ray);
		verticalLine(cub, cub->ray, x);
	}
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

void	lengthRay(t_cub * cub, t_ray *ray)
{
	while (1)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->map.x += ray->step.x;
			ray->whichSide = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->map.y += ray->step.y;
			ray->whichSide = 1;
		}
		if (cub->map->matrix[ray->map.y][ray->map.x] > 0) {
			break ;
		}
	}
	if (ray->whichSide == 0)
		ray->perpWallDist = (ray->map.x - cub->cam->player_pos.x + (1 - ray->step.x) / 2) / ray->ray.x;
	else
		ray->perpWallDist = (ray->map.y - cub->cam->player_pos.y + (1 - ray->step.y) / 2) / ray->ray.y;
	ray->rayLength = (int)(cub->data->height / ray->perpWallDist);
}

void	verticalLine(t_cub *cub, t_ray *ray, int x)
{
	int	y;

	ray->startP = cub->data->height / 2 - ray->rayLength / 2;
	ray->endP = cub->data->height / 2 + ray->rayLength / 2;
	if (ray->startP < 0)
		ray->startP = 0;
	if (ray->endP > cub->data->height) 
		ray->endP = cub->data->height;
	y = -1;
	while (++y < ray->startP)
		setpixel(cub->data, x, y, map_sky); // setpixel(cub->data, x, y, cub->map->C) // apres avoir bien parse la couleur
	while (++y <= ray->endP)
		setpixel(cub->data, x, y, map_wall); // une fonction qui transpose pour le bon pixel en fonction de la texture
	while (++y < cub->data->height - 1)
		setpixel(cub->data, x, y, map_floor);	
}
