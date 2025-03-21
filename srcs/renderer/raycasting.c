/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:51:37 by tespandj          #+#    #+#             */
/*   Updated: 2024/12/01 01:03:59 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/raycasting.h"

void	raycast(t_cub *cub)
{
	t_mgam2i	pos;
	t_mgam2i	view;


	pos = (t_mgam2i){cub->cam->player_pos.x * SPACE, cub->cam->player_pos.y * SPACE};
	view = (t_mgam2i){pos.x + (cub->ray->ray.x * 20), pos.y + (cub->ray->ray.y * 20)};

	cub->ray->x = -1;
	miniMap(cub, cub->data);
	printf("width :%d\n",cub->data->width);
	while (++cub->ray->x < cub->data->width)
	{
		dda(cub, cub->ray);
		verticalLine(cub, cub->ray, cub->ray->x);
		// view = (t_mgam2i){pos.x + (cub->ray->ray.x * 100), pos.y + (cub->ray->ray.y * 100)};
		// view = (t_mgam2i){pos.x + (fabs(pos.x - cub->ray->ray.x)),
		// 			pos.y + (fabs(pos.y - cub->ray->ray.y)) };
		// ligne(cub, pos, view);


	}
	// printf("pos %d et %d\n", pos.x, pos.y);
	// printf("view %d et %d\n", view.x, view.y);
	ligne(cub, pos, view);

	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

int	wallHit(t_cub *cub, double x, double y)
{
	if ((x < 0 || x > cub->map->l) || (y < 0 || y > cub->map->L))
		return (1);
	if (cub->map->matrix[(int)y][(int)x] == '1')
		return (1);
	return 0;
}

void	setpixel(t_data *data, int x, int y, int color)
{
	char *dst;
	if ((x < data->width && x > 0) && (y < data->height && y > 0))
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	// else
	// 	printf("Bouffon t'ecris en dehors\n");
}
