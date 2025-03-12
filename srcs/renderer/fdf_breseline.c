/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_breseline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 05:58:28 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/09 05:58:29 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	breseline(t_cub *cub, t_mgam2i a, t_mgam2i b)
{
	t_bsl	t;

	bslinit(&t, a, b);
	cub->map->color_bsl = 0x757083;
	if (t.dy1 <= t.dx1)
		sbto(cub, &t);
	else
	{
		if (t.dy >= 0)
		{
			t.x = a.x;
			t.y = a.y;
			t.ye = b.y;
		}
		else
		{
			t.x = b.x;
			t.y = b.y;
			t.ye = a.y;
		}
		if (wallHit(cub, t.x, t.y))
			return ;
		setpixel(cub->data, t.x, t.y, cub->map->color_bsl);
		slto(cub, &t);
	}
}

void	bslinit(t_bsl *t, t_mgam2i a, t_mgam2i b)
{
	t->dx = b.x - a.x;
	t->dy = b.y - a.y;
	t->dx1 = tabs(t->dx);
	t->dy1 = tabs(t->dy);
	t->px = 2 * t->dy1 - t->dx1;
	t->py = 2 * t->dx1 - t->dy1;
	if (t->dy1 <= t->dx1)
	{
		if (t->dx >= 0)
		{
			t->x = a.x;
			t->y = a.y;
			t->xe = b.x;
		}
		else
		{
			t->x = b.x;
			t->y = b.y;
			t->xe = a.x;
		}
	}
}

void	slto(t_cub *cub, t_bsl *t)
{
	while (t->y < t->ye)
	{
		t->y++;
		if (t->py <= 0)
			t->py = t->py + 2 * t->dx1;
		else
		{
			if ((t->dx < 0 && t->dy < 0) || (t->dx > 0 && t->dy > 0))
				t->x++;
			else
				t->x--;
			t->py = t->py + 2 * (t->dx1 - t->dy1);
		}
		if (wallHit(cub, t->x, t->y))
			return ;
		setpixel(cub->data, t->x, t->y, cub->map->color_bsl);
	}
}

void	sbto(t_cub *cub, t_bsl *t)
{
	setpixel(cub->data, t->x, t->y, cub->map->color_bsl);
	while (t->x < t->xe)
	{
		t->x++;
		if (t->px < 0)
			t->px = t->px + 2 * t->dy1;
		else
		{
			if ((t->dx < 0 && t->dy < 0) || (t->dx > 0 && t->dy > 0))
				t->y++;
			else
				t->y--;
			t->px = t->px + 2 * (t->dy1 - t->dx1);
		}
		if (wallHit(cub, t->x, t->y))
			return ;
		setpixel(cub->data, t->x, t->y, cub->map->color_bsl);
	}
}

int	tabs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
