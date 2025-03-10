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

int	cub3d(struct s_cub *cub)
{
	raycast(cub);
	mlx_key_hook(cub->data->win, keyPressed, cub);
	// mlx_hook(cub->data->win, KeyPress, 1L << 0, &press, cub->data->mlx);
	// mlx_hook(cub->data->win, KeyRelease, 1L << 1, &release, cub->data->mlx);
	mlx_hook(cub->data->win, DestroyNotify, 0, &end_win, cub);
	mlx_loop(cub->data->mlx);
	freend(cub);
	return (0);
}
