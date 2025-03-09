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

	fprintf(stderr, ">>>>>>>>>>>>>>>>>>>> %f\n", cub->cam->player_pos.x);
	fprintf(stderr, ">>>>>>>>>>>>>>>>>>>> %f\n", cub->cam->player_pos.y);
	pos = (t_mgam2i){cub->cam->player_pos.x, cub->cam->player_pos.y};

	view = (t_mgam2i){cub->cam->look.x, cub->cam->look.y};

	x = -1;
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
			setpixel(cub->data, x, y, 0);
	}
	draw_map(cub, cub->data);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
			setpixel(cub->data, pos.x + i, pos.y + j, 0xFF0000);
			// setpixel(cub->data, pos.x + i + cub->data->x_off, pos.y + j + cub->data->y_off, 0xFF0000);
		/* code */
	}

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

int return_color(char c)
{
	if (c == '0')
		return 0xAEB8FE;
	if (c == '1')
		return 0x27187E;
	// if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
	// 	return 0xFF8600;
	return 0xAEB8FE;
	return 0xAB12CD;
}

void draw_map(t_cub *cub, t_data *data)
{
	int h = cub->map->L;
	int l = cub->map->l - 1;
	int size = h * l;

	for (int i = 0; i < size; i++)
	{
		int row = i / l; // FIXED: Correct row calculation
		int col = i % l; // FIXED: Correct column calculation
		for (size_t k = 0; k < (SPACE * SPACE); ++k)
			setpixel(data, (col * SPACE + (k / SPACE)) + data->x_off,
				 (row * SPACE + (k % SPACE)) + data->y_off, return_color(cub->map->matrix[row][col]));
	}
	int player_x = (int)(cub->cam->player_pos[0] * SPACE) + data->x_off;
	int player_y = (int)(cub->cam->player_pos[1] * SPACE) + data->y_off;
	int player_size = 5; // Taille du carré du joueur
	// printf("appel de draw_map et donc joueuru\n");
	for (int i = 0; i < player_size; i++)
		for (int j = 0; j < player_size; j++)
			setpixel(data, player_x + i, player_y + j, 0xFF8600); // Rouge pour le joueur
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

offset.x = cub->data->width - (SPACE * cub->map->l);
offset.y = cub->data->height - (SPACE * cub->map->L);
// h_right.x = cub->data->x_off + SPACE * cub;
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