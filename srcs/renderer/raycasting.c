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
	ray->startp = -ray->raylength / 2 + cub->data->height / 2 ;
	if (ray->startp < 0)
		ray->startp = 0;
	ray->endp = ray->raylength / 2 + cub->data->height / 2;
	if (ray->endp >= cub->data->height)
		ray->endp = cub->data->height - 1;
	while (++y < ray->startp + cub->ray->head)
		setpixel(cub->data, cub->ray->x, y, cub->map->ceiling);
	xpos(cub, cub->ray);
	txt_pixel(cub, cub->ray);
	y = ray->endp - 1 + ray->head;
	while (++y < cub->data->height)
		setpixel(cub->data, cub->ray->x, y, cub->map->floor);
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!((x < data->width && x >= 0) && (y < data->height && y >= 0)))
	{
		printf("t'ecries en dehors\n");
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

uint	getpixel(t_txt *txt, int x, int y)
{
	char	*dst;

	dst = txt->addr + (y * txt->size_line + x * (txt->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
