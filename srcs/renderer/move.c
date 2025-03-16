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

	theta = 10 * (M_PI / 180);
	// if (key == XK_Left)
	// {
	// 	cam->look.x += 20 *(cos(-theta) - sin(-theta));
	// 	cam->look.y += 20 *(sin(-theta) - cos(-theta));
	// }
	// else
	// {
	// 	cam->look.x -= 20 *(cos(theta) - sin(theta));
	// 	cam->look.y -= 20 *(sin(theta) - cos(theta));
	// }
	// printf("After : {%f, %f}\n", cam->look[0], cam->look[1]);
	(void)theta;
	(void)key;
	(void)cam;
}


//	player->dir_deg -= ROTATION_SPEED;
// 	if (player->dir_deg < 0)
// 		player->dir_deg += 359;
// 	player->old_dir_x = player->dir.x;
// 	player->dir.x = player->dir.x * cos(ROTATION_SPEED)
// 		- player->dir.y * sin(ROTATION_SPEED);
// 	player->dir.y = player->old_dir_x * sin(ROTATION_SPEED)
// 		+ player->dir.y * cos(ROTATION_SPEED);
// 	player->old_plane_x = data->ray->plane.x;
// 	data->ray->plane.x = data->ray->plane.x * cos(ROTATION_SPEED)
// 		- data->ray->plane.y * sin(ROTATION_SPEED);
// 	data->ray->plane.y = player->old_plane_x * sin(ROTATION_SPEED)
// 		+ data->ray->plane.y * cos(ROTATION_SPEED);


// if (map->left_pressed)
// 	{
// 		oldir = map->camera.dir.x;
// 		map->camera.dir.x = map->camera.dir.x * cos(-rot_speed)
// 			- map->camera.dir.y * sin(-rot_speed);
// 		map->camera.dir.y = oldir * sin(-rot_speed) + map->camera.dir.y
// 			* cos(-rot_speed);
// 		old_planex = map->camera.plane.x;
// 		map->camera.plane.x = map->camera.plane.x * cos(-rot_speed)
// 			- map->camera.plane.y * sin(-rot_speed);
// 		map->camera.plane.y = old_planex * sin(-rot_speed) + map->camera.plane.y
// 			* cos(-rot_speed);
// 	}