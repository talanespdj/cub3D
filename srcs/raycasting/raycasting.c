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

	y = -1;
	// reset_cub(cub);
	while (++y < cub->data->height)
	{
		x = -1;
		while (++x < cub->data->width)
			setpixel(cub->data, x, y, 0x8895B3);
	}
	mlx_xpm_file_to_image(cub->data->mlx, cub->map->NO, &cub->data->width, &cub->data->height);
	aff_map(cub);
	aff_cam(cub);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	(void)x;
}

void	reset_cub(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (++y <= cub->data->height)
	{
		x = -1;
		while (++x <= cub->data->width)
			setpixel(cub->data, x, y, 0);
	}
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

void	aff_cam(t_cub *cub)
{
	int	xz;
	int	yz;

	yz = cub->cam->y + cub->map->zoom / 2;
	while (--yz > cub->cam->y - cub->map->zoom / 2)
	{
		xz = cub->cam->x + cub->map->zoom / 2;
		while (--xz > cub->cam->x - cub->map->zoom / 2)
			setpixel(cub->data, xz, yz, 255);
	}
}

void	aff_map(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	while (cub->map->matrix[++y])
	{
		x = -1;
		while (cub->map->matrix[y][++x])
		{
			if (cub->map->matrix[y][x] == '1')
				setblock(cub, x, y, 0x001514);
			else if (cub->map->matrix[y][x] == '0')
				setblock(cub, x, y, 0xFFE1EA);
		}
	}
}

void	setblock(t_cub *cub, int x, int y, int color)
{
	int	xblock;
	int	yblock;
	int	save_x;
	int	save_y;
	int	zoom;

	zoom = cub->map->zoom / 4;
	yblock = cub->data->height / 2 + (y * zoom);
	save_y = yblock;
	while (--yblock > save_y - (2 * y * zoom))
	{
		xblock = cub->data->width / 2 + (x * zoom);
		save_x = xblock;
		while (--xblock > save_x - (2 * x * zoom))
			setpixel(cub->data, xblock, yblock, color);
	}
}

void	fill_win(t_cub *cub)
{
	raycast(cub);
	mlx_key_hook(cub->data->win, key_press, cub);
	mlx_hook(cub->data->win, 17, 0, &end_win, cub);
	mlx_loop(cub->data->mlx);
}
