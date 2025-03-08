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
	t_point pt;
	t_point pt2;

	// pt.x = cub->cam->player_pos[0];
	// pt.y = cub->cam->player_pos[1];
	
	pt.x = cub->cam->player_pos[0];
	pt.y = cub->cam->player_pos[1];
	pt2.x = cub->cam->look[0];
	pt2.y = cub->cam->look[1];

	x = -1;
	// mlx_xpm_file_to_image(cub->data->mlx, cub->map->NO, &cub->data->width, &cub->data->height);
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
			setpixel(cub->data, x, y, 0);
	}
	draw_map(cub->map, cub->data);
	breseline(cub, pt, pt2);
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
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return 0xFF8600;
	return 0xAB12CD;
			
}

void	draw_map(t_map *map, t_data *data)
{
	size_t SPACE = 32;
	int h = map->L;
	int l = map->l - 1;
	int size = h * l;
	int	x_off = data->width / 2 - (l / 2 * SPACE);
	int	y_off = data->height / 2 - (h / 2 * SPACE);

	for (int i = 0; i < size; i++)
	{
		int row = i / l;  // FIXED: Correct row calculation
		int col = i % l;  // FIXED: Correct column calculation
		for (size_t k = 0; k < (SPACE * SPACE); k++)
			setpixel(data, (col * SPACE + (k / SPACE)) + x_off, (row * SPACE + (k % SPACE)) + y_off, return_color(map->matrix[row][col]));
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