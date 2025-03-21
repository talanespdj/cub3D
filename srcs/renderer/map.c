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

int	return_color(char c)
{
	if (c == '0')
		return (MAP_VOID);
	return (MAP_WALL);
}

void	minimap(t_cub *cub, t_data *data)
{
	t_mgam2i	pos;
	size_t		j;
	int			i;
	int			row;
	int			col;
	int			size;

	i = -1;
	size = cub->map->L * (cub->map->l - 1);
	pos = (t_mgam2i){cub->cam->player_pos.x - 1, cub->cam->player_pos.y - 1};
	while (++i < size)
	{
		j = -1;
		row = i / (cub->map->l - 1);
		col = i % (cub->map->l - 1);
		while (++j < (SPACE * SPACE))
			setpixel(data, (col * SPACE + (j / SPACE)) + data->x_off,
				(row * SPACE + (j % SPACE)) + data->y_off, return_color(cub->map->matrix[row][col]));
	}
	i = -1;
	while (++i <= RATIO_PLAYER)
	{
		j = -1;
		while (++j <= RATIO_PLAYER)
			setpixel(cub->data, (cub->cam->player_pos.x * SPACE) + i, (cub->cam->player_pos.y * SPACE) + j, MAP_PLAYER);
	}
}
