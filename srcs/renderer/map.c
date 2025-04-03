/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 01:22:35 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/30 01:22:40 by tespandj         ###   ########.fr       */
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
}
