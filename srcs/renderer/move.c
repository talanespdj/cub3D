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

int	mousemotion(t_cub *cub)
{
	int	x;
	int	y;
	
	mlx_mouse_get_pos(cub->data->mlx, cub->data->win, &x, &y);
	if (x < cub->cam->mouse_x - 2 || x > cub->cam->mouse_x + 2)
	{
		if (x < cub->cam->mouse_x - 2)
			lookmove(cub->ray, cub->cam, XK_Left);
		else
			lookmove(cub->ray, cub->cam, XK_Right);
		mlx_mouse_move(cub->data->mlx, cub->data->win, cub->data->width / 2, cub->data->height / 2);
	}
	return (0);
}

void	movement(t_cub *cub)
{
	t_mgam2f	posplayer;

	posplayer = (t_mgam2f){cub->cam->player_pos.x, cub->cam->player_pos.y};
	if (cub->keys.w == 1)
		if (!wallhit(cub, posplayer.x + (cub->cam->look.x * MOVESPEED),
				posplayer.y + (cub->cam->look.y * MOVESPEED)))
			cub->cam->player_pos += (t_mgam2f){cub->cam->look.x * MOVESPEED, cub->cam->look.y * MOVESPEED};
	if (cub->keys.s == 1)
		if (!wallhit(cub, posplayer.x - (cub->cam->look.x * MOVESPEED),
					posplayer.y - (cub->cam->look.y * MOVESPEED)))
			cub->cam->player_pos -= (t_mgam2f){cub->cam->look.x * MOVESPEED, cub->cam->look.y * MOVESPEED};
	if (cub->keys.a == 1)
		if (!wallhit(cub, posplayer.x - (cub->ray->plane.x * MOVESPEED),
					posplayer.y - (cub->ray->plane.y * MOVESPEED)))
			cub->cam->player_pos -= (t_mgam2f){cub->ray->plane.x * MOVESPEED, cub->ray->plane.y * MOVESPEED};
	if (cub->keys.d == 1)
		if (!wallhit(cub, posplayer.x + (cub->ray->plane.x * MOVESPEED),
			posplayer.y + (cub->ray->plane.y * MOVESPEED)))
				cub->cam->player_pos += (t_mgam2f){cub->ray->plane.x * MOVESPEED, cub->ray->plane.y * MOVESPEED};
	if (cub->keys.l == 1)
		lookmove(cub->ray, cub->cam, XK_Left);
	if (cub->keys.r == 1)
		lookmove(cub->ray, cub->cam, XK_Right);
	// mousemotion(cub);
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
