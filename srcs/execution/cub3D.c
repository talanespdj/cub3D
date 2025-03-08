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
	cub->data->x_off = cub->data->width / 2 - (cub->map->l / 2 * cub->data->SPACE);
	cub->data->y_off = cub->data->height / 2 - (cub->map->L / 2 *cub->data->SPACE);
	while (++y && cub->map->matrix[y])
	{
		x = -1;
		while (++x && cub->map->matrix[y][x])
		{
			if (cub->map->matrix[y][x] == 'N' || cub->map->matrix[y][x] == 'S' || cub->map->matrix[y][x] == 'E' || cub->map->matrix[y][x] == 'O') {
				cub->cam->player_pos[0] += x + cub->data->x_off;
				cub->cam->player_pos[1] += y + cub->data->y_off;
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
