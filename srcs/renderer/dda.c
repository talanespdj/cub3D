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

int	tabs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char *dst;
	if ((x < data->width && x > 0) && (y < data->height && y > 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	// else
	// 	printf("Bouffon t'ecris en dehors\n");
}

void	dda(t_cub *cub, t_mgam2i a, t_mgam2i b)
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
		if (wallHit(cub, save.x, save.y))
			return ;
		setpixel(cub->data, round(save.x), round(save.y), 0x757083); // put pixel at (X,Y) 
		save += inc;
	}
}
