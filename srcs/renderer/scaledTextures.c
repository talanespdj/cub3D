/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratioTextures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:40:49 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/21 23:42:16 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"

static t_txt	*cardinalstxt(t_cub *cub)
{
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

void	texture_pixel(t_cub *cub, t_ray *ray)
{
	int	length;
	int	color = 0;
	int	pas;
	t_txt	*dir;

	dir = cardinalstxt(cub);
	ray->startp = ray->startp - 1;
	if (ray->startp < 0)
		ray->startp = 0;
	length = ray->raylength;
	pas = 1 * cub->txt[NO]->height / length;
	while (++ray->startp < ray->endp)
	{
		// color = (texture_buffer)[NO][cub->txt[NO]-> * ((int)pos & (MMAP - 1)) + tex_x];
		setpixel(cub->data, cub->ray->x, ray->startp, color);
	}
	(void)dir;
	(void)pas;
}
