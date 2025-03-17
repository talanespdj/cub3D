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
	
	look = cub->cam->look;
	posPlayer = (t_mgam2i){cub->cam->player_pos.x, cub->cam->player_pos.y};
	if (cub->keys.w == 1)
	{
		if (!wallHit(cub, posPlayer.x + look.x * moveSpeed, posPlayer.y))
			cub->cam->player_pos.x += look.x * moveSpeed;
		if (!wallHit(cub, posPlayer.x, posPlayer.y + look.y * moveSpeed))
			cub->cam->player_pos.y += look.y * moveSpeed;
	}
	if (cub->keys.s == 1)
	{
		if (!wallHit(cub, posPlayer.x - look.x * moveSpeed, posPlayer.y))
			cub->cam->player_pos.x -= look.x * moveSpeed;
		if (!wallHit(cub, posPlayer.x, posPlayer.y - look.y * moveSpeed))
			cub->cam->player_pos.y -= look.y * moveSpeed;
	}
	if (cub->keys.a == 1)
	{
		if (!wallHit(cub, posPlayer.x + look.y * moveSpeed, posPlayer.y))
			cub->cam->player_pos.x += look.y * moveSpeed;
		if (!wallHit(cub, posPlayer.x, posPlayer.y - look.x * moveSpeed))
			cub->cam->player_pos.y -= look.x * moveSpeed;
	}
	if (cub->keys.d == 1)
	{
		if (!wallHit(cub, posPlayer.x - look.y * moveSpeed, posPlayer.y))
			cub->cam->player_pos.x -= look.y * moveSpeed;
		if (!wallHit(cub, posPlayer.x, posPlayer.y + look.x * moveSpeed))
			cub->cam->player_pos.y += look.x * moveSpeed;
	}
	if (cub->keys.l == 1)
		lookMove(cub->ray, cub->cam, XK_Left);
	if (cub->keys.r == 1)
		lookMove(cub->ray, cub->cam, XK_Right);
}

void	lookMove(t_ray *ray, t_cam *cam, int key)
{
	double	saveLook;
	double	savePlane;
	double	rotate;

	rotate = rotateSpeed;
	if (key == XK_Left)
		rotate = -rotateSpeed;
	saveLook = cam->look.x;
	cam->look.x = cam->look.x * cos(rotate) - cam->look.y * sin(rotate);
	cam->look.y = saveLook * cos(rotate) + cam->look.y * sin(rotate);
	savePlane = ray->plane.x;
	ray->plane.x = ray->plane.x * cos(rotate) - ray->plane.y * sin(rotate);
	ray->plane.y = savePlane * cos(rotate) + ray->plane.y * sin(rotate);
}

int	wallHit(t_cub *cub, int x, int y)
{
	if ((x < 0 || x > cub->map->l) || (y < 0 || y > cub->map->L - 1))
		return (1);
	if (cub->map->matrix[y][x] == '1')
		return (1);
	return 0;
}