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

void	raycast(t_cub *cub)
{
	int y;
	int x;
	t_point pos;
	t_point view;

	// pos.x = cub->cam->player_pos[0];
	// pos.y = cub->cam->player_pos[1];
	pos.x = cub->cam->player_pos[0] + cub->data->SPACE;
	pos.y = cub->cam->player_pos[1] + cub->data->SPACE;

	// pos.x = cub->cam->_2dPlayer[0];
	// pos.y = cub->cam->_2dPlayer[1];

	// view.x = cub->cam->look[0];
	// view.y = cub->cam->look[1];
	view.x = pos.x + 20;
	view.y = pos.y + 20;

	// printf("%d // %d\n", view.x, view.y);
	printf("%d // %d\n", pos.x, pos.y);

	x = -1;
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
			setpixel(cub->data, x, y, 0);
	}
	// draw_map(cub->map, cub->data);
	setpixel(cub->data, pos.x, pos.y, 0xFF8600);
	setpixel(cub->data, view.x, view.y, 0xFF8600);
	// 0xFF8600
	printf("pos joueur : x %f\t\ty %f\n", cub->cam->player_pos[0] + cub->data->SPACE, cub->cam->player_pos[1] + cub->data->SPACE);
	// breseline(cub, pos, view);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

void	setpixel(t_data *data, int x, int y, int color)
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

int return_color(char c)
{

	if (c == '0')
		return 0xAEB8FE;
	if (c == '1')
		return 0x27187E;
	// if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
	// 	return 0xFF8600;
	return 0xAB12CD;
			
}

void	draw_map(t_map *map, t_data *data)
{
	int h = map->L;
	int l = map->l - 1;
	int size = h * l;
	
	for (int i = 0; i < size; i++)
	{
		int row = i / l;  // FIXED: Correct row calculation
		int col = i % l;  // FIXED: Correct column calculation
		for (size_t k = 0; k < (data->SPACE * data->SPACE); k++)
			setpixel(data, (col * data->SPACE + (k / data->SPACE)) + data->x_off,
			(row * data->SPACE + (k % data->SPACE)) + data->y_off, return_color(map->matrix[row][col]));
	}
}

void fill_win(t_cub *cub)
{
	raycast(cub);
	mlx_key_hook(cub->data->win, keyPressed, cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	mlx_hook(cub->data->win, 17, 0, &end_win, cub);
	mlx_loop(cub->data->mlx);
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