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
	t_mgam2i	posPlayer;
	t_mgam2f	look;
	t_mgam2f	plane;
	
	look = cub->cam->look;
	plane = cub->ray->plane;
	posPlayer = (t_mgam2i){cub->cam->player_pos.x, cub->cam->player_pos.y};
	if (cub->keys.w == 1)
		if (!wallHit(cub, posPlayer.x + (look.x * moveSpeed), posPlayer.y + (look.y * moveSpeed)))
			cub->cam->player_pos += (t_mgam2f){look.x * moveSpeed, look.y * moveSpeed};
	if (cub->keys.s == 1)
		if (!wallHit(cub, posPlayer.x - (look.x * moveSpeed), posPlayer.y - (look.y * moveSpeed)))
			cub->cam->player_pos -= (t_mgam2f){look.x * moveSpeed, look.y * moveSpeed};
	if (cub->keys.a == 1)
		if (!wallHit(cub, posPlayer.x - (plane.x * moveSpeed), posPlayer.y - (plane.y * moveSpeed)))
			cub->cam->player_pos -= (t_mgam2f){plane.x * moveSpeed, plane.y * moveSpeed};
	if (cub->keys.d == 1)
		if (!wallHit(cub, posPlayer.x + (plane.x * moveSpeed), posPlayer.y + (plane.y * moveSpeed)))
			cub->cam->player_pos += (t_mgam2f){plane.x * moveSpeed, plane.y * moveSpeed};
	if (cub->keys.l == 1)
		lookMove(cub->ray, cub->cam, XK_Left);
	if (cub->keys.r == 1)
		lookMove(cub->ray, cub->cam, XK_Right);
}

void	lookMove(t_ray *ray, t_cam *cam, int key)
{
	double	saveLook;
	double	savePlane;
	double	speed;

	speed = rotateSpeed;
	if (key == XK_Left)
		speed = -rotateSpeed;
	saveLook = cam->look.x;
	cam->look.x = cam->look.x * cos(speed) - cam->look.y * sin(speed);
	cam->look.y = saveLook * sin(speed) + cam->look.y * cos(speed);

	savePlane = ray->plane.x;
	ray->plane.x = ray->plane.x * cos(speed) - ray->plane.y * sin(speed);
	ray->plane.y = savePlane * sin(speed) + ray->plane.y * cos(speed);
}

int	wallHit(t_cub *cub, int x, int y)
{
	if ((x < 0 || x > cub->map->l) || (y < 0 || y > cub->map->L - 1))
		return (1);
	if (cub->map->matrix[y][x] == '1')
		return (1);
	return 0;
}
