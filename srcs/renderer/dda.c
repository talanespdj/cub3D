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

int	_2point_slope(t_mgam2f a, t_mgam2f b) {
	return ((int)(b.y - a.y) / (b.x - a.x));
}


void	dda(t_cub *cub, t_mgam2i a, t_mgam2i b)
{ 
	int dx = b.x - a.x; 
	int dy = b.y - a.y; 

	int steps = tabs(dx) > tabs(dy) ? tabs(dx) : tabs(dy); 

	float Xinc = dx / (float)steps; 
	float Yinc = dy / (float)steps; 

	float X = a.x; 
	float Y = a.y; 
	for (int i = 0; i <= steps; i++) { 
		if (wallHit(cub, X, Y))
			return ;
		setpixel(cub->data, round(X), round(Y), cub->map->color_bsl); // put pixel at (X,Y) 
		X += Xinc;
		Y += Yinc;
	}
} 
