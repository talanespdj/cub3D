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

	y = -1;
	/// print the whole mMap
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
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
		}
	}

	// map qui bouge en fonction de la pos du joueur

			// segfault quand on regarde dans matrix -> voir quand est ce que les valeurs peuvent etre mauvaises

	/*
	t_mgam2f	pos;
	t_mgam2f	x_limits;
	t_mgam2f	y_limits;
	t_mgam2i	xi_limits;
	t_mgam2i	yi_limits;


	pos = cub->cam->player_pos;
	x_limits.x = pos.x - 8 > 0 ? pos.x - 8 : 0;
	x_limits.y = pos.x + 8 < cub->map->l ? pos.x + 8 : cub->map->l;
	y_limits.x = pos.y - 8 > 0 ? pos.y - 8 : 0;
	y_limits.y = pos.y + 8 < cub->map->l ? pos.y + 8 : cub->map->L;

	printf("x_limits = {%f, %f}\n", x_limits.x, x_limits.y); // d'où je dois aller horizontalement dans la map 
	printf("y_limits = {%f, %f}\n", y_limits.x, y_limits.y); // pareil verticalement

	// while (y_limits.x < (y_limits.y))
	// {
	// 	x = (int)x_limits.x - 1;
	// 	while (++x < (int)x_limits.y)
	// 		setpixel(cub->data, x, (int)y_limits.x, mmap_color(matrix[(int)y_limits.x][x]));
	// 	y_limits.x++;
	// }

	xi_limits.x = pos.x - 8 > 0 ? pos.x - 8 : 0;
	xi_limits.y = pos.x + 8 < cub->map->l ? pos.x + 8 : cub->map->l;
	yi_limits.x = pos.y - 8 > 0 ? pos.y - 8 : 0;
	yi_limits.y = pos.y + 8 < cub->map->l ? pos.y + 8 : cub->map->L;

	printf("xi_limits = {%d, %d}\n", xi_limits.x, xi_limits.y); // d'où je dois aller horizontalement dans la map 
	printf("yi_limits = {%d, %d}\n", yi_limits.x, yi_limits.y); // pareil verticalement

	r = -1;
	t = -1;
	while (yi_limits.x < (yi_limits.y - 1))
	{
		x = (int)xi_limits.x - 1;
		while (++x < (int)xi_limits.y && matrix[(int)yi_limits.x] && matrix[(int)yi_limits.x][x])
		{
			if (matrix[(int)yi_limits.x][x] == '0' || matrix[(int)yi_limits.x][x] == '1')
			{
				{
					color = mmap_color(matrix[(int)yi_limits.x][x]);
					r = -1;
					while (++r < MMAP)
					{
						t = -1;
						while (++t < MMAP)
							setpixel(cub->data, x * MMAP + r, yi_limits.x * MMAP + t, color);
					}
				}
			}

		}
		yi_limits.x++;
	}
	*/

}
