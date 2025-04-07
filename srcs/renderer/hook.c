/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:32:00 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/07 13:32:05 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

int	press(int key, t_cub *cub)
{
	if (key == XK_w)
		cub->keys.w = 1;
	if (key == XK_s)
		cub->keys.s = 1;
	if (key == XK_a)
		cub->keys.a = 1;
	if (key == XK_d)
		cub->keys.d = 1;
	if (key == XK_Left)
		cub->keys.l = 1;
	if (key == XK_Right)
		cub->keys.r = 1;
	if (key == XK_Tab)
	{
		if (cub->keys.tab == 1)
			cub->keys.tab = 0;
		else
			cub->keys.tab = 1;
	}
	if (key == XK_Shift_L)
		cub->keys.shift = 1;
	if (key == XK_Escape)
		end_win(cub);
	return (0);
}

int	release(int key, t_cub *cub)
{
	if (key == XK_w)
		cub->keys.w = 0;
	if (key == XK_s)
		cub->keys.s = 0;
	if (key == XK_a)
		cub->keys.a = 0;
	if (key == XK_d)
		cub->keys.d = 0;
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			cub->keys.l = 0;
		else
			cub->keys.r = 0;
	}
	if (key == XK_Shift_L)
		cub->keys.shift = 0;
	if (key == XK_Up)
		cub->keys.up = 0;
	if (key == XK_Down)
		cub->keys.down = 0;
	return (0);
}

void	lookmove(t_ray *ray, t_cam *cam, int key)
{
	double	savelook;
	double	saveplane;
	double	rotate;

	rotate = ROTATESPEED;
	if (key == XK_Left)
		rotate = -ROTATESPEED;
	savelook = cam->look.x;
	cam->look.x = cam->look.x * cos(rotate) - cam->look.y * sin(rotate);
	cam->look.y = savelook * sin(rotate) + cam->look.y * cos(rotate);
	saveplane = ray->plane.x;
	ray->plane.x = ray->plane.x * cos(rotate) - ray->plane.y * sin(rotate);
	ray->plane.y = saveplane * sin(rotate) + ray->plane.y * cos(rotate);
}
