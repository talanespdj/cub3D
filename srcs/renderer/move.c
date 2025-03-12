/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 02:55:32 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/11 02:55:34 by tespandj         ###   ########.fr       */
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
	return (0);
}

void	movement(t_cub *cub)
{
	t_mgam2i posPlayer = (t_mgam2i){cub->cam->player_pos.x + (ratio_player / 2),
				  cub->cam->player_pos.y + (ratio_player / 2)};
	if (cub->keys.w == 1)
		if (!wallHit(cub, posPlayer.x, posPlayer.y - dist_player_move))
			cub->cam->player_pos -= (t_mgam2f){0, RATIO_MOVE};
	if (cub->keys.s == 1)
		if (!wallHit(cub, posPlayer.x, posPlayer.y + dist_player_move))
			cub->cam->player_pos += (t_mgam2f){0, RATIO_MOVE};
	if (cub->keys.a == 1)
		if (!wallHit(cub, posPlayer.x - dist_player_move, posPlayer.y))
			cub->cam->player_pos -= (t_mgam2f){RATIO_MOVE, 0};
	if (cub->keys.d == 1)
		if (!wallHit(cub, posPlayer.x + dist_player_move, posPlayer.y))
			cub->cam->player_pos += (t_mgam2f){RATIO_MOVE, 0};
	if (cub->keys.l == 1)
		lookMove(cub->cam, XK_Left);
	if (cub->keys.r == 1)
		lookMove(cub->cam, XK_Right);
}

void	lookMove(t_cam *cam, int key)
{
	double theta;

	theta = 0.015;
	if (key == XK_Left)
	{
		cam->oldlook.x = cam->look.x;
		cam->look.x = (cam->look.x * cos(theta)) - ( cam->look.y * sin(theta));
		cam->look.y = (cam->oldlook.x  * sin(theta)) + (cam->look.y * cos(theta));
	}
	else
	{
	// 	cam->look.x -= (cos(theta) - sin(theta));
	// 	cam->look.y -= (sin(theta) - cos(theta));
		cam->oldlook.x = cam->look.x;
		cam->look.x = (cam->look.x * cos(-theta)) - ( cam->look.y * sin(-theta));
		cam->look.y = (cam->oldlook.x * sin(-theta)) + ( cam->look.y * cos(-theta));
	}
	printf("After : {%f, %f}\n", cam->look[0], cam->look[1]);
}

