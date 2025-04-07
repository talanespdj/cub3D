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
#include "../../includes/raycasting.h"

void	movement(t_cub *cub)
{
	double		ms;

	ms = MS;
	if (cub->keys.shift)
		ms = 0.015;
	if (cub->keys.w)
		forward(cub, ms);
	if (cub->keys.s)
		backward(cub, ms);
	if (cub->keys.a)
		left(cub, ms);
	if (cub->keys.d)
		right(cub, ms);
	if (cub->keys.l)
		lookmove(cub->ray, cub->cam, XK_Left);
	if (cub->keys.r)
		lookmove(cub->ray, cub->cam, XK_Right);
}

void	forward(t_cub *cub, double ms)
{
	t_mgam2f	posplayer;
	t_mgam2f	look;

	look = cub->cam->look;
	posplayer = (t_mgam2f)cub->cam->player_pos;
	if (!wallhit(cub, posplayer.x + look.x * ms, posplayer.y))
		cub->cam->player_pos.x = cub->cam->player_pos.x + (look.x * ms);
	if (!wallhit(cub, posplayer.x, posplayer.y + look.y * ms))
		cub->cam->player_pos.y = cub->cam->player_pos.y + (look.y * ms);
}

void	backward(t_cub *cub, double ms)
{
	t_mgam2f	posplayer;
	t_mgam2f	look;

	look = cub->cam->look;
	posplayer = (t_mgam2f)cub->cam->player_pos;
	if (!wallhit(cub, posplayer.x - look.x * ms, posplayer.y))
		cub->cam->player_pos.x -= look.x * ms;
	if (!wallhit(cub, posplayer.x, posplayer.y - look.y * ms))
		cub->cam->player_pos.y -= look.y * ms;
}

void	left(t_cub *cub, double ms)
{
	t_mgam2f	posplayer;
	t_mgam2f	plane;

	plane = cub->ray->plane;
	posplayer = (t_mgam2f)cub->cam->player_pos;
	if (!wallhit(cub, posplayer.x - plane.x * ms, posplayer.y))
		cub->cam->player_pos.x -= plane.x * ms;
	if (!wallhit(cub, posplayer.x, posplayer.y - plane.y * ms))
		cub->cam->player_pos.y -= plane.y * ms;
}

void	right(t_cub *cub, double ms)
{
	t_mgam2f	posplayer;
	t_mgam2f	plane;

	plane = cub->ray->plane;
	posplayer = (t_mgam2f)cub->cam->player_pos;
	if (!wallhit(cub, posplayer.x + plane.x * ms, posplayer.y))
		cub->cam->player_pos.x += plane.x * ms;
	if (!wallhit(cub, posplayer.x, posplayer.y + plane.y * ms))
		cub->cam->player_pos.y += plane.y * ms;
}
