/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:51:37 by tespandj          #+#    #+#             */
/*   Updated: 2024/12/01 01:03:59 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void raycast(t_cub *cub)
{
	int y;
	int x;
	t_mgam2i pos;
	t_mgam2i view;

	pos = (t_mgam2i){cub->cam->player_pos.x, cub->cam->player_pos.y};
	view = (t_mgam2i){cub->cam->look.x, cub->cam->look.y};

	x = -1;
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
			setpixel(cub->data, x, y, 0);
	}
	miniMap(cub, cub->data);
	printf("joueur pos : {%d, %d}\n", pos.x, pos.y);
	printf("view : {%d, %d}\n", view.x, view.y);
	breseline(cub, pos, view);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

void setpixel(t_data *data, int x, int y, int color)
{
	char *dst;
	if ((x < data->width && x > 0) && (y < data->height && y > 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	// else
	// 	printf("Bouffon t'ecris en dehors\n");
}

// mlx_hook(cub->data->win, XK_w, (1L<<0), &press_w, cub);
// mlx_hook(cub->data->win, XK_w, (1L<<1), &release_w, cub);

// mlx_hook(cub->data->win, XK_s, (1L<<0), &press_s, cub);
// mlx_hook(cub->data->win, XK_s, (1L<<1), &release_s, cub);

// mlx_hook(cub->data->win, XK_a, (1L<<0), &press_a, cub);
// mlx_hook(cub->data->win, XK_a, (1L<<1), &release_a, cub);

// mlx_hook(cub->data->win, XK_d, (1L<<0), &press_d, cub);
// mlx_hook(cub->data->win, XK_d, (1L<<1), &release_d, cub);

// mlx_hook(cub->data->win, XK_Left, (1L<<0), &press_left, cub);
// mlx_hook(cub->data->win, XK_Left, (1L<<1), &release_left, cub);

// mlx_hook(cub->data->win, XK_Right, (1L<<0), &press_right, cub);
// mlx_hook(cub->data->win, XK_Right, (1L<<1), &release_right, cub);
