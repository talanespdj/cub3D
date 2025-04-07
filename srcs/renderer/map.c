/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:22:35 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 15:48:18 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	mmap_color(t_cub *cub, char c, int x, int y)
{
	int	color;
	int	r;
	int	t;

	color = 0;
	if (c == '0')
		color = 0x353831;
	else if (c == '1')
		color = 0x090C08;
	r = -1;
	while (++r < MMAP)
	{
		t = -1;
		while (++t < MMAP)
			setpixel(cub->data, x * MMAP + r, y * MMAP + t, color);
	}
}

static void	player(t_cub *cub, double x, double y, double radius);

void	minimap(t_cub *cub, char **matrix)
{
	int	x;
	int	y;

	y = 0;
	if (((cub->map->lar - 2) * MMAP > cub->data->height / 3)
		|| (cub->map->lon - 2) * MMAP > cub->data->width / 3)
	{
		cub->minimap = 0;
		return ;
	}
	while (matrix[++y + 1])
	{
		x = -1;
		while (matrix[y][++x + 1])
			if (matrix[y][x] == '0' || matrix[y][x] == '1')
				mmap_color(cub, matrix[y][x], x, y);
	}
	player(cub, cub->cam->player_pos.x, cub->cam->player_pos.y, 4.0);
}

static void	player(t_cub *cub, double x, double y, double radius)
{
	t_mgam2i	delta;	
	int			w;
	int			h;

	w = -1;
	x *= MMAP;
	y *= MMAP;
	while (++w < radius * 2)
	{
		h = -1;
		while (++h < radius * 2)
		{
			delta = (t_mgam2i){radius - w, radius - h};
			if ((delta.x * delta.x + delta.y * delta.y) <= (radius * radius))
				setpixel(cub->data, (int)(x + delta.x),
					(int)(y + delta.y), 0x949396);
		}
	}
}
