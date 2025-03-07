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
	int	y;
	int	x;
	t_point		pt;
	t_point		pt2;

	pt.x = cub->cam->player_pos[0];
	pt.y = cub->cam->player_pos[1];
	// cub->cam->player_pos
	pt2.x = cub->cam->look[0];
	pt2.y = cub->cam->look[1];

	printf("point 1 ..//     %d   %d\n", pt.x, pt.y);
	printf("point 1 ..//     %d   %d\n", pt2.x, pt2.y);

	x = -1;
	// mlx_xpm_file_to_image(cub->data->mlx, cub->map->NO, &cub->data->width, &cub->data->height);
	while (++x < cub->data->width)
	{
		y = -1;
		while (++y < cub->data->height)
			setpixel(cub->data, x, y, 0);
	}

	breseline(cub, pt, pt2);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x < data->width && x > 0) && (y < data->height && y > 0))
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}


void	fill_win(t_cub *cub)
{
	raycast(cub);
	mlx_key_hook(cub->data->win, key_press, cub);
	
	mlx_hook(cub->data->win, key_press, (1L<<0), &press, cub);
	mlx_hook(cub->data->win, key_press, (1L<<1), &release, cub);

	mlx_hook(cub->data->win, 17, 0, &end_win, cub);
	mlx_loop(cub->data->mlx);
}
