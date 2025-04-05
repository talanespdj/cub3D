/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:46:10 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 16:04:38 by tespandj         ###   ########.fr       */
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
	t_mgam2i	pos2d;
	int			verti;
	int			horiz;

	verti = -1;
	horiz = -1;
	pos2d = (t_mgam2i){(int)cub->cam->player_pos.x, (int)cub->cam->player_pos.y};
	// if (pos2d.x != (int)x && pos2d.y != (int)y)
	// {
	// 	if ((int)x > pos2d.x)
	// 		horiz = 1;
	// 	if ((int)y > pos2d.y)
	// 		verti = 1;
		
	// 	if (cub->map->matrix[pos2d.y + verti][pos2d.x] == '1' && cub->map->matrix[pos2d.y][pos2d.x + horiz] == '1')
	// 		return (0);
	// 	printf("on check les cases {%d, %d} et {%d, %d}\n", pos2d.y + verti, pos2d.x, pos2d.y, pos2d.x + horiz);
	// 	printf("ou on veut aller : %d, %d\n", (int)x, (int)y);
	// }
	if (cub->map->matrix[(int)y][(int)x] == '1' || cub->map->matrix[(int)y][(int)x] == '.')
		return (1);
	return (0);
}
