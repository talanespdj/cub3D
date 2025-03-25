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

void	texture_pixel(t_cub *cub, t_ray *ray)
{
	int	length;
	int	colorwall;

	colorwall = 0x880000;
	if (ray->whichside)
		colorwall = 0xAA0000;
	length = ray->raylength;
	ray->startp = ray->startp - 1;
	if (ray->startp < 0)
		ray->startp = 0;
	while (++ray->startp < ray->endp)
		setpixel(cub->data, cub->ray->x, ray->startp, colorwall);
}
