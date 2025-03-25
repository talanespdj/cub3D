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

static void	ddainit(t_cub *cub, t_ray *ray);

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
		// if (ray->map.x > cub->map->l || ray->map.y > cub->map->L) { // arrive quand il y a des tab dans la map
		// 	printf("on essaie de check {%d, %d}\n", ray->map.x, ray->map.y);
		// 	freend(cub);
		// }
		if (cub->map->matrix[ray->map.y][ray->map.x] == '1')
			break ;
	}
	ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
	if (ray->whichside)
		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
	ray->raylength = cub->data->height / ray->perpwalldist;
}

static void	ddainit(t_cub *cub, t_ray *ray)
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

int	wallhit(t_cub *cub, double x, double y)
{
	if ((x < 0 || x > cub->map->l - 1) || (y < 0 || y > cub->map->L))
		return (1);
	if (cub->map->matrix[(int)y][(int)x] == '1')
		return (1);
	return 0;
}