/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:55:32 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 15:42:11 by tespandj         ###   ########.fr       */
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
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			cub->keys.l = 1;
		else
			cub->keys.r = 1;
	}
	if (key == XK_Tab)
	{
		if (cub->keys.tab == 1)
			cub->keys.tab = 0;
		else
			cub->keys.tab = 1;
	}
	if (key == XK_Shift_L)
		cub->keys.shift = 1;
	if (key == XK_Up)
		cub->keys.up = 1;
	if (key == XK_Down)
		cub->keys.down = 1;
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

void	movement(t_cub *cub)
{
	t_mgam2f	posplayer;
	t_mgam2f	look;
	t_mgam2f	plane;
	double		ms;

	ms = MS;
	if (cub->keys.shift)
		ms = 0.015;
	look = cub->cam->look;
	plane = cub->ray->plane;
	posplayer = (t_mgam2f){cub->cam->player_pos.x, cub->cam->player_pos.y};
	if (cub->keys.w)
	{
		if (!wallhit(cub, posplayer.x + look.x * ms, posplayer.y))
			cub->cam->player_pos.x += look.x * ms;
		if (!wallhit(cub, posplayer.x ,posplayer.y + look.y * ms))
			cub->cam->player_pos.y += look.y * ms;
	}
	if (cub->keys.s)
	{
		if (!wallhit(cub, posplayer.x - look.x * ms, posplayer.y))
			cub->cam->player_pos.x -= look.x * ms;
		if (!wallhit(cub, posplayer.x ,posplayer.y - look.y * ms))
			cub->cam->player_pos.y -= look.y * ms;
	}
	if (cub->keys.a)
	{
		if (!wallhit(cub, posplayer.x - plane.x * ms, posplayer.y))
			cub->cam->player_pos.x -= plane.x * ms;
		if (!wallhit(cub, posplayer.x ,posplayer.y - plane.y * ms))
			cub->cam->player_pos.y -= plane.y * ms;
	}
	if (cub->keys.d)
	{
		if (!wallhit(cub, posplayer.x + plane.x * ms, posplayer.y))
			cub->cam->player_pos.x += plane.x * ms;
		if (!wallhit(cub, posplayer.x ,posplayer.y + plane.y * ms))
			cub->cam->player_pos.y += plane.y * ms;
	}
	if (cub->keys.l)
		lookmove(cub->ray, cub->cam, XK_Left);
	if (cub->keys.r)
		lookmove(cub->ray, cub->cam, XK_Right);
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
