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

static void	ddainit(t_ray *ray, t_cam *cam);

void	dda(t_cub *cub, t_ray *ray)
{
	ray->camerax = 2 * ray->x / (double)cub->data->width - 1;
	ddainit(cub->ray, cub->cam);
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
		if (cub->map->matrix[ray->map.y][ray->map.x] != '0')
			break ;
	}
	cub->ray->txt = cardinalstxt(cub, cub->ray);
}

static void	ddainit(t_ray *ray, t_cam *cam)
{
	ray->ray = (t_mgam2f){cam->look.x + (ray->plane.x * ray->camerax),
		cam->look.y + (ray->plane.y * ray->camerax)};
	ray->map = (t_mgam2i){(int)cam->player_pos.x, (int)cam->player_pos.y};
	ray->deltadist = (t_mgam2f){fabs(1 / ray->ray.x), fabs(1 / ray->ray.y)};
	ray->step = (t_mgam2i){1, 1};
	if (ray->ray.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (cam->player_pos.x - ray->map.x) * ray->deltadist.x;
	}
	else
		ray->sidedist.x = (ray->map.x + 1.0 - cam->player_pos.x)
			* ray->deltadist.x;
	if (ray->ray.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (cam->player_pos.y - ray->map.y) * ray->deltadist.y;
	}
	else
		ray->sidedist.y = (ray->map.y + 1.0 - cam->player_pos.y)
			* ray->deltadist.y;
}

int	wallhit(t_cub *cub, double x, double y)
{
	if (cub->map->matrix[(int)y][(int)x] == '1' || cub->map->matrix[(int)y][(int)x] == '.')
		return (1);
	return (0);
}
