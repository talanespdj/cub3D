/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 05:58:01 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/09 05:58:04 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"

void	draw_disk(t_data *data, int xc, int yc);

int	return_color(char c)
{
	if (c == '0')
		return map_void;
	if (c == '1')
		return map_wall;
	// if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
	// 	return 0xFF8600; // former : 0xFF8600
	return map_void; //
}

void	miniMap(t_cub *cub, t_data *data)
{
	t_mgam2i pos;
	int	i;
	size_t	j;
	int	size;
	int	row;
	int	col;

	i = -1;
	size = cub->map->L * (cub->map->l - 1);
	pos = (t_mgam2i){cub->cam->player_pos.x - 1, cub->cam->player_pos.y - 1};
	while (++i < size)
	{
		j = -1;
		row = i / (cub->map->l - 1); // FIXED: Correct row calculation
		col = i % (cub->map->l - 1); // FIXED: Correct column calculation
		while (++j < (SPACE * SPACE))
			setpixel(data, (col * SPACE + (j / SPACE)) + data->x_off,
				 (row * SPACE + (j % SPACE)) + data->y_off, return_color(cub->map->matrix[row][col]));
	}
	i = -1;
	while (++i <= ratio_player)
	{
		j = -1;
		while (++j <= ratio_player)
			setpixel(cub->data, pos.x + i, pos.y + j, 0xFF0000);
	}
}

void	draw_disk(t_data *data, int xc, int yc)
{
	for (int y = yc - ratio_player; y <= yc + ratio_player; y++)
		for (int x = xc - ratio_player; x <= xc + ratio_player; x++)
			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= ratio_player * ratio_player)
				setpixel(data, x, y, map_wall);
}