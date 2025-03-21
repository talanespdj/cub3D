/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:46:10 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/09 22:46:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"

void	ddainit(t_cub *cub, t_ray *ray)
{
	ray->camerax = 2 * ray->x / (double)cub->data->width - 1;
	cub->ray->ray = (t_mgam2f){cub->cam->look.x + (cub->ray->plane.x * ray->camerax),
		cub->cam->look.y + (cub->ray->plane.y * ray->camerax)};
	cub->ray->map = (t_mgam2i){(int)cub->cam->player_pos.x, (int)cub->cam->player_pos.y};
	cub->ray->deltadist = (t_mgam2f){fabs(1 / cub->ray->ray.x), fabs(1 / cub->ray->ray.y)};
	if (cub->ray->ray.x < 0)
	{
		cub->ray->step.x = -1;
		cub->ray->sidedist.x = (cub->cam->player_pos.x - cub->ray->map.x) * cub->ray->deltadist.x;
	}
	else
	{
		cub->ray->step.x = 1;
		cub->ray->sidedist.x = (cub->ray->map.x + 1.0 - cub->cam->player_pos.x) * cub->ray->deltadist.x;
	}
	if (cub->ray->ray.y < 0)
	{
		cub->ray->step.y = -1;
		cub->ray->sidedist.y = (cub->cam->player_pos.y - cub->ray->map.y) * cub->ray->deltadist.y;
	}
	else
	{
		cub->ray->step.y = 1;
		cub->ray->sidedist.y = (cub->ray->map.y + 1.0 - cub->cam->player_pos.y) * cub->ray->deltadist.y;
	}
}

void	dda(t_cub *cub, t_ray *ray)
{
	ddainit(cub, cub->ray);
	while (1)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->whichside = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->whichside = 1;
		}
		// if (ray->map.x > cub->map->l || ray->map.y > cub->map->L) {
		// 	printf("on essaie de check {%d, %d}\n", ray->map.x, ray->map.y);
		// 	freend(cub);
		// }
		if (cub->map->matrix[ray->map.y][ray->map.x] == '1')
			break ;
	}
	if (ray->whichside == 0)
		ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
	else
		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
	ray->raylength = (int)(cub->data->height / ray->perpwalldist);
}

void	verticaline(t_cub *cub, t_ray *ray, int x)
{
	int	y;
	int	colorwall;

	ray->startp = -ray->raylength / 2 + cub->data->height / 2;
	ray->endp = ray->raylength / 2 + cub->data->height / 2;
	if (ray->startp < 0)
		ray->startp = 0;
	if (ray->endp > cub->data->height)
		ray->endp = cub->data->height - 1;
	colorwall = 0x880000;
	if (ray->whichside)
		colorwall = 0xAA0000;
	y = -1;
	while (++y < ray->startp)
		setpixel(cub->data, x, y, MAP_SKY); // setpixel(cub->data, x, y, cub->map->ceiling) // apres avoir bien parse la couleur
	while (y < ray->endp)
	{
		setpixel(cub->data, x, y, colorwall); // une fonction qui transpose pour le bon pixel en fonction de la texture
		y++;
	}
	while (y < cub->data->height)
	{
		setpixel(cub->data, x, y, MAP_FLOOR);
		y++;
	}
}
