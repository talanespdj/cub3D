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

int	looping(t_cub *cub)
{
	movement(cub);
	cub->ray->x = -1;
	while (++cub->ray->x < cub->data->width)
	{
		dda(cub, cub->ray);
		raycast(cub, cub->ray);
	}
	// minimap(cub, cub->map->matrix);	
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
	return 0;
}

int	cub3d(struct s_cub *cub)
{
	cub->txt[NO]->name = tdup(cub->txt[NO]->name);
	cub->txt[NO]->width = 0;
	cub->txt[NO]->height = 0;
	cub->txt[NO]->img = mlx_xpm_file_to_image(cub->data->mlx, cub->txt[NO]->name, &cub->txt[NO]->width, &cub->txt[NO]->height);
	if (cub->txt[NO]->img)
		printf("fonctionne\n");
	else 
		printf("marche pas\n");
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->txt[NO]->img, 0, 0);
	mlx_hook(cub->data->win, KeyPress, 1L << 0, &press, cub);
	mlx_hook(cub->data->win, KeyRelease, 1L << 1, &release, cub);
	// mlx_hook(cub->data->win, MotionNotify, 1L << 6, &mousemotion, cub); // doesn't work on mac
	mlx_hook(cub->data->win, DestroyNotify, 0, &end_win, cub);
	mlx_loop_hook(cub->data->mlx, looping, cub);
	mlx_mouse_hide(cub->data->mlx, cub->data->win);
	mlx_loop(cub->data->mlx);
	return (0);
}
