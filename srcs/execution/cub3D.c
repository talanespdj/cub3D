/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:21:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 21:29:46 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	def_pos_player(t_cub *cub)
{
	int	x;
	int	y;

	y = -1;
	cub->data->x_off = cub->data->width / 2 - (cub->map->l / 2 * SPACE);
	cub->data->y_off = cub->data->height / 2 - (cub->map->L / 2 * SPACE);

	while (cub->map->matrix[++y])
	{
		x = -1;
		while (cub->map->matrix[y][++x])
		{
			if (cub->map->matrix[y][x] == 'N' || cub->map->matrix[y][x] == 'S' || cub->map->matrix[y][x] == 'E' || cub->map->matrix[y][x] == 'O') {
				cub->cam->player_pos.x = x * SPACE + cub->data->x_off;
				cub->cam->player_pos.y = y * SPACE + cub->data->y_off;
				return ;
			}
		}
	}
}

int	cub3d(struct s_cub *cub)
{
	def_pos_player(cub);
	fill_win(cub);
	freend(cub);
	return (0);
}
