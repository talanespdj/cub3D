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

static	void	set_mmap(t_cub *cub)
{
	cub->mmap = MMAP;
	if (((cub->map->lar - 2) * MMAP > cub->data->height / 3)
		|| (cub->map->lon - 2) * MMAP > cub->data->width / 3)
	{
		if (((cub->map->lar - 2) * MMAP / 2 > cub->data->height / 3)
			|| (cub->map->lon - 2) * MMAP / 2 > cub->data->width / 3)
		{
			cub->minimap = 0;
			return ;
		}
		cub->mmap = MMAP / 2;
	}
}

int	looping(t_cub *cub)
{
	movement(cub);
	cub->ray->x = -1;
	while (++cub->ray->x < cub->data->width)
	{
		dda(cub, cub->ray);
		xpos(cub, cub->ray);
		raycast(cub, cub->ray);
	}
	if (cub->minimap && cub->keys.tab == 1)
		minimap(cub, cub->map->matrix);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win,
		cub->data->img, 0, 0);
	return (0);
}

int	cub3d(t_cub *cub, t_data *data)
{
	set_mmap(cub);
	mlx_hook(data->win, KeyPress, 1L << 0, &press, cub);
	mlx_hook(data->win, KeyRelease, 1L << 1, &release, cub);
	mlx_hook(data->win, DestroyNotify, 0, &end_win, cub);
	mlx_loop_hook(data->mlx, looping, cub);
	mlx_loop(data->mlx);
	return (0);
}
