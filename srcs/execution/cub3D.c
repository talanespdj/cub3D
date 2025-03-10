/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:21:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 21:29:46 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void handleKeyPress(t_cub *cub)
{
	// printf("douqnwdoinqwodiq\n");
	if (cub->keys.w == 1)
	{
		cub->cam->player_pos -= (t_mgam2f){0, RATIO_MOVE};
		cub->cam->look -= (t_mgam2f){0, RATIO_MOVE};
	}
	if (cub->keys.s == 1)
	{
		cub->cam->player_pos += (t_mgam2f){0, RATIO_MOVE};
		cub->cam->look += (t_mgam2f){0, RATIO_MOVE};
	}
	if (cub->keys.a == 1)
	{
		cub->cam->player_pos -= (t_mgam2f){RATIO_MOVE, 0};
		cub->cam->look -= (t_mgam2f){RATIO_MOVE, 0};
	}
	if (cub->keys.d == 1)
	{
		printf("BEFORE %f %f\n", cub->cam->player_pos.x, cub->cam->player_pos.y);
		cub->cam->player_pos += (t_mgam2f){RATIO_MOVE, 0};
		cub->cam->look += (t_mgam2f){RATIO_MOVE, 0};
		printf("AFTER %f %f\n", cub->cam->player_pos.x, cub->cam->player_pos.y);
	}
	if (cub->keys.l == 1)
		lookMove(cub->cam, XK_Left);
	if (cub->keys.r == 1)
		lookMove(cub->cam, XK_Right);
}

int my_loop(t_cub *cub)
{
	handleKeyPress(cub);
	raycast(cub);
	return 0;
}

int cub3d(struct s_cub *cub)
{
	// raycast(cub);
	// mlx_key_hook(cub->data->win, keyPressed, cub);
	mlx_hook(cub->data->win, KeyPress, 1L << 0, &press, cub);
	mlx_hook(cub->data->win, KeyRelease, 1L << 1, &release, cub);
	mlx_hook(cub->data->win, DestroyNotify, 0, &end_win, cub);
	mlx_loop_hook(cub->data->mlx, my_loop, cub);
	mlx_loop(cub->data->mlx);
	freend(cub);
	return (0);
}
