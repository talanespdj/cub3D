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

void	raycast(t_cub *cub, t_ray *ray)
{
	int	y;

	y = -1;
	ray->startp = -ray->raylength / 2 + cub->data->height / 2;
	if (ray->startp < 0)
		ray->startp = -1;
	ray->endp = ray->raylength / 2 + cub->data->height / 2;
	if (ray->endp >= cub->data->height)
		ray->endp = cub->data->height - 1;
	while (++y < ray->startp)
		setpixel(cub->data, cub->ray->x, y, MAP_SKY);
	texture_pixel(cub, cub->ray);
	y = ray->endp - 1;
	while (++y < cub->data->height)
		setpixel(cub->data, cub->ray->x, y, MAP_FLOOR);
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char *dst;
	if ((x < data->width && x >= 0) && (y < data->height && y >= 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		printf("Bouffon t'ecris en dehors\n");
}