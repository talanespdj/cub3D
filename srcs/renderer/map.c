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

int	mmap_color(char c)
{
	if (c == '0')
		return (0x353831);
	else if (c == '1')
		return (0x090C08);
	return (0);
}

static void	player(t_cub *cub, double x, double y, double radius);

void	minimap(t_cub *cub, char **matrix)
{
	int	r;
	int	t;
	int	x;
	int	y;
	int	color;

	y = 1;
	while (matrix[y + 1])
	{
		x = 0;
		if (y * MMAP > cub->data->height / 3)
			break ;
		while (matrix[y][x + 1])
		{
			if (matrix[y][x] == '0' || matrix[y][x] == '1')
			{
				color = mmap_color(matrix[y][x]);
				r = -1;
				while (++r < MMAP)
				{
					t = -1;
					while (++t < MMAP)
						setpixel(cub->data, x * MMAP + r, y * MMAP + t, color);
				}
			}
			x++;
		}
		y++;
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
					(int)(y + delta.y), cub->map->floor);
		}
	}
}
