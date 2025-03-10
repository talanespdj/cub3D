/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 04:04:04 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/10 04:04:06 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

int valid_move(int key, t_cub *cub)
{
	t_mgam2i pos;

	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player / 2),
			 cub->cam->player_pos.y + (ratio_player / 2)};

	if (key == XK_w)
	{
		// if (pos.y - dist_player_move < 0)
		if (wallHit(cub, pos.x, pos.y - dist_player_move))
			return (0);
	}
	if (key == XK_s)
	{
		// if (pos.y + dist_player_move > cub->data->height)
		if (wallHit(cub, pos.x, pos.y + dist_player_move))
			return (0);
	}
	if (key == XK_a)
	{
		// if (pos.x - dist_player_move < 0)
		if (wallHit(cub, pos.x - dist_player_move, pos.y))
			return (0);
	}
	if (key == XK_d)
	{
		// if (pos.x + dist_player_move > cub->data->width)
		if (wallHit(cub, pos.x + dist_player_move, pos.y))
			return (0);
	}

	return (1);
}

void lookMove(t_cam *cam, int key)
{
	double theta;

	theta = 100 * (M_PI / 180);
	if (key == XK_Left)
	{
		cam->look.x += 100 * (cos(-theta) - sin(-theta));
		cam->look.y += 100 * (sin(-theta) - cos(-theta));
	}
	else
	{
		cam->look.x += 100 * (cos(theta) - sin(theta));
		cam->look.y += 100 * (sin(theta) - cos(theta));
	}
	printf("After : {%f, %f}\n", cam->look[0], cam->look[1]);
}

int press(int key, void *tmp)
{
	t_cub *cub = (t_cub *)tmp;
	t_mgam2i pos;
	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player)-cub->map->l / 4,
			 cub->cam->player_pos.y + (ratio_player)-cub->map->L / 2};
	if (key == XK_w)
	{
		cub->keys.w = 1;
		// cub->cam->player_pos -= (t_mgam2f){0, 0};
		// cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_s)
	{
		cub->keys.s = 1;
		// cub->cam->player_pos += (t_mgam2f){0, 0};
		// cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_a)
	{
		cub->keys.a = 1;
		// cub->cam->player_pos -= (t_mgam2f){0, 0};
		// cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_d)
	{
		cub->keys.d = 1;
		// cub->cam->player_pos += (t_mgam2f){0, 0};
		// cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			cub->keys.l = 1;
		else
			cub->keys.r = 1;
		// if (key == XK_Left)
		// lookMove(cub->cam, XK_Left);
		// else
		// 	lookMove(cub->cam, XK_Right);
	}
	// raycast(cub);
	return (0);
}

int release(int key, void *tmp)
{
	t_cub *cub = (t_cub *)tmp;
	if (key == XK_w)
	{
		cub->keys.w = 0;
		// cub->cam->player_pos -= (t_mgam2f){0, 0};
		// cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_s)
	{
		cub->keys.s = 0;
		// cub->cam->player_pos += (t_mgam2f){0, 0};
		// cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_a)
	{
		cub->keys.a = 0;
		// cub->cam->player_pos -= (t_mgam2f){0, 0};
		// cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_d)
	{
		cub->keys.d = 0;
		// cub->cam->player_pos += (t_mgam2f){0, 0};
		// cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			cub->keys.l = 0;
		else
			cub->keys.r = 0;
		// if (key == XK_Left)
		// lookMove(cub->cam, XK_Left);
		// else
		// 	lookMove(cub->cam, XK_Right);
	}
	if (key == XK_Escape)
		end_win(cub);
	return (0);
}
