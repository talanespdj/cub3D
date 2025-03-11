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

// int	tabs(int n)
// {
// 	if (n < 0)
// 		return (-n);
// 	return (n);
// }

int	_2point_slope(t_mgam2f a, t_mgam2f b) {
	return ((int)(b.y - a.y) / (b.x - a.x));
}

t_mgam2i	roundf_tmgam2f(t_mgam2f a) {
	t_mgam2i	new_a;

	new_a.x = roundf(a.x);
	new_a.y = roundf(a.y);
	return (new_a);
}

void	dda(t_cub *cub, t_mgam2f a, t_mgam2f b) {

	t_mgam2i	newP;
	t_mgam2i	oldPoint;
	t_mgam2i	endPoint;
	int		slope;
	int		steps;
	int i = 0;
	
	steps = tabs(b.x - a.x);
	if (tabs(b.y - a.y) > steps)
		steps = tabs(b.y - a.y);
	newP = roundf_tmgam2f(a);
	oldPoint = roundf_tmgam2f(a);
	endPoint = roundf_tmgam2f(b);
	slope = _2point_slope(a, b);
	// while (newP.x != endPoint.x || newP.y != endPoint.y) {
	while (++i < steps) {
		printf("i [%d]\n", i);
		if (slope == 1)
			newP = oldPoint + (t_mgam2i){1, 1};
		else if (slope < 1)
			newP = (t_mgam2i){oldPoint.x + 1, oldPoint.y + slope};
		else if (slope > 1)
			newP = (t_mgam2i){oldPoint.x + 1 / slope, oldPoint.y + 1};
		if (wallHit(cub, newP.x, newP.y))
			return ;
		setpixel(cub->data, newP.x, newP.y, 0xFFB8FE);
		oldPoint = newP;
	}
}


