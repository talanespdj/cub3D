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
#include "../../includes/cub3d.h"

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
	int i = -1;
	
	newP = roundf_tmgam2f(a);
	oldPoint = roundf_tmgam2f(a);
	endPoint = roundf_tmgam2f(b);
	slope = _2point_slope(a, b);
	while (newP.x != endPoint.x) {
		if (slope == 1)
			newP = oldPoint + (t_mgam2i){1, 1};
		else if (slope < 1)
			newP = (t_mgam2i){oldPoint.x + 1, oldPoint.y + slope};
		else if (slope > 1)
			newP = (t_mgam2i){oldPoint.x + 1 / slope, oldPoint.y + 1};
		setpixel(cub->data, newP.x, newP.y, 0xFFB8FE);
		oldPoint = newP;
		++i;
		printf("i [%d]\n", i);
	}
}
