/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaledTextures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:40:49 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/26 04:48:17 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"

t_txt	*cardinalstxt(t_cub *cub, t_ray *ray)
{
	if (ray->whichside == 0)
		ray->perpwalldist = ray->sidedist.x - ray->deltadist.x;
	else
		ray->perpwalldist = ray->sidedist.y - ray->deltadist.y;
	ray->raylength = (int)cub->data->height / ray->perpwalldist;
	if (cub->ray->whichside)
	{
		if (cub->ray->ray.y > 0)
			return (cub->txt[EA]);
		return (cub->txt[WE]);
	}
	if (cub->ray->ray.x > 0)
		return (cub->txt[NO]);
	return (cub->txt[SO]);
}

void	xpos(t_cub *cub, t_ray *ray)
{
	double		wallx;

	if (!ray->whichside)
		wallx = cub->cam->player_pos.y + ray->perpwalldist * ray->ray.y;
	else
		wallx = cub->cam->player_pos.x + ray->perpwalldist * ray->ray.x;
	wallx -= (int)wallx;
	ray->texx = (int)(wallx * (double)ray->txt->width);
	if ((!ray->whichside && ray->ray.x > 0)
		|| (ray->whichside && ray->ray.y < 0))
		ray->texx = ray->txt->width - ray->texx - 1;
}

void	txt_pixel(t_cub *cub, t_ray *ray)
{
	double	pas;
	double	texpos;
	int		color;
	int		length;

	length = ray->raylength;
	pas = 1.0 * ray->txt->height / length;
	texpos = (ray->startp - cub->data->height / 2 + ray->raylength / 2) * pas;
	while (ray->startp < ray->endp)
	{
		color = getpixel(ray->txt, ray->texx, (int)texpos);
		setpixel(cub->data, cub->ray->x, ray->startp + ray->head, color);
		texpos += pas;
		ray->startp++;
	}
}
