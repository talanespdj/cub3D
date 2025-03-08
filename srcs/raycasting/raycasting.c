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
	x = -1;
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
		setpixel(cub->data, x, y, 0);
	}
	draw_map(cub->map, cub->data);
	// breseline(cub, origin, offset);
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

int	return_color(char c)
{
	if (c == '0')
		return 0xAEB8FE;
	if (c == '1')
		return 0x27187E;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return 0xFF8600;
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


/*	JUSTE ON VIBE

t_point pos;
t_point view;

t_point offset;
t_point origin = {0, 0};

t_point h_left;
t_point h_right;
t_point b_left;
t_point b_right;

if (cub->cam->player_pos[0] < cub->map->l / 2)
	pos.x = cub->cam->player_pos[0];

pos.y = cub->cam->player_pos[1];



h_left.x = cub->data->x_off;
h_left.y = cub->data->y_off;

offset.x = cub->data->width - (cub->data->SPACE * cub->map->l);
offset.y = cub->data->height - (cub->data->SPACE * cub->map->L);
// h_right.x = cub->data->x_off + cub->data->SPACE * cub;
// h_right.y = cub->data->y_off;

// origin.x = 0;
// origin.y = 0;

// c_bas_droit.x = offset.x +;

pos.x = offset.x;
pos.y = offset.y;
// printf("%d \\ %d\n", view.x, view.y);


printf("%d eetttttttt %d\n", pos.x, pos.y);
(void)pos;
(void)view;
(void)h_left;
(void)h_right;
(void)b_left;
(void)b_right;

*/