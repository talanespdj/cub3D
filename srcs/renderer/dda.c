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

void	lengthRay(t_cub * cub, t_ray *ray);

int	tabs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ddaInit(t_cub *cub, t_ray *ray)
{
	double	cameraX;

	cameraX = 2 * ray->x / (double)cub->data->width - 1;
	cub->ray->ray = (t_mgam2f){cub->cam->look.x + (cub->ray->plane.x * cameraX),
				cub->cam->look.y + (cub->ray->plane.y * cameraX)};
	cub->ray->map = (t_mgam2i){(int)cub->cam->player_pos.x, (int)cub->cam->player_pos.y};
	cub->ray->deltaDist = (t_mgam2f){fabs(1 / cub->ray->ray.x), fabs(1 / cub->ray->ray.y)};
	if (cub->ray->ray.x < 0)
	{
		cub->ray->step.x = -1;
		cub->ray->sideDist.x = (cub->cam->player_pos.x - cub->ray->map.x) * cub->ray->deltaDist.x;
	}
	else
	{
		cub->ray->step.x = 1;
		cub->ray->sideDist.x = (cub->ray->map.x + 1.0 - cub->cam->player_pos.x) * cub->ray->deltaDist.x;
	}
	if (cub->ray->ray.y < 0)
	{
		cub->ray->step.y = -1;
		cub->ray->sideDist.y = (cub->cam->player_pos.y - cub->ray->map.y) * cub->ray->deltaDist.y;
	}
	else
	{
		cub->ray->step.y = 1;
		cub->ray->sideDist.y = (cub->ray->map.y + 1.0 - cub->cam->player_pos.y) * cub->ray->deltaDist.y;
	}



	// if (cub->ray->ray.x >= 0)
	// {
	// 	cub->ray->step.x = 1;
	// 	cub->ray->sideDist.x = (cub->ray->map.x + 1.0 - cub->cam->player_pos.x) * cub->ray->deltaDist.x;
	// }
	// else
	// 	cub->ray->sideDist.x = (cub->cam->player_pos.x - cub->ray->map.x) * cub->ray->deltaDist.x;
	// if (cub->ray->ray.y >= 0)
	// {
	// 	cub->ray->step.y = 1;
	// 	cub->ray->sideDist.y = (cub->ray->map.y + 1.0 - cub->cam->player_pos.y) * cub->ray->deltaDist.y;
	// }
	// else
	// 	cub->ray->sideDist.y = (cub->cam->player_pos.y - cub->ray->map.y) * cub->ray->deltaDist.y;
}


void	dda(t_cub *cub, t_ray *ray)
{
	ddaInit(cub, cub->ray);
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
		printf("%d et %d\n", ray->step.y, ray->step.x);
		// printf("%d et %d\n", ray->map.y, ray->map.x);
		if (ray->map.y > cub->map->L || ray->map.x > cub->map->l) {
			printf("TU SORS DE LA MAP DUCON\n\n\n\t\t");
			printf("%d et %d\n", ray->map.y, ray->map.x);
			exit (1);
		}
		if (cub->map->matrix[ray->map.y][ray->map.x] == '1')
			break ;
	}
	if (ray->whichSide == 0)
		ray->perpWallDist = ray->sideDist.x - ray->deltaDist.x;
	else
		ray->perpWallDist = ray->sideDist.y - ray->deltaDist.y;
	printf("pwd : %f\n", ray->perpWallDist);
	ray->rayLength = (int)(cub->data->height / ray->perpWallDist);
}

void	verticalLine(t_cub *cub, t_ray *ray, int x)
{
	int	y;
	int colorwall;
	// printf("raylenght : %d\n", ray->rayLength);
	ray->startP = -ray->rayLength / 2 + cub->data->height / 2;
	ray->endP = ray->rayLength / 2 + cub->data->height / 2;
	if (ray->startP < 0)
		ray->startP = 0;
	if (ray->endP > cub->data->height) 
		ray->endP = cub->data->height - 1;
	colorwall = 0x880000;
	if (ray->whichSide)
		colorwall = 0xAA0000;
	// printf("startP : %d , endP: %d\n", ray->startP, ray->endP);
	y = -1;
	while (++y < ray->startP)
		setpixel(cub->data, x, y, map_sky); // setpixel(cub->data, x, y, cub->map->C) // apres avoir bien parse la couleur
	while (y < ray->endP)
	{
		setpixel(cub->data, x, y, colorwall); // une fonction qui transpose pour le bon pixel en fonction de la texture
		y++;
	}
	while (y < cub->data->height)
	{
		setpixel(cub->data, x, y, map_floor);
		y++;
	}
	printf("je passe ici \n");

}

void	ligne(t_cub *cub, t_mgam2i a, t_mgam2i b)
{ 
	t_mgam2f	inc;
	t_mgam2f	save;
	int		steps;
	int		dx;
	int		dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	steps = tabs(dx) > tabs(dy) ? tabs(dx) : tabs(dy); 
	inc = (t_mgam2f){dx / (float)steps, dy / (float)steps};
	save = (t_mgam2f){a.x, a.y};
	for (int i = 0; i <= steps; i++)
	{ 
		// if (wallHit(cub, save.x, save.y))
		// 	return ;
		setpixel(cub->data, round(save.x), round(save.y), 0xFF0000); // put pixel at (X,Y) 
		save += inc;
	}
} 