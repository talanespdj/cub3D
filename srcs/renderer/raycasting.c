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
	// t_mgam2f	posf;
	// t_mgam2f	viewf;


	// pour breseline 
	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player / 2), cub->cam->player_pos.y + (ratio_player / 2)};
	view = (t_mgam2i){pos.x + cub->cam->look.x, pos.y + cub->cam->look.y}; // temporaire
	// le point view doit etre sur une extremite de l'ecran, multiplier par le vecteur look qui lui est affecte suivant 
	// l'incrementation/decrementation de l'angle du regard
	// les x y du point view ne peuvent pas etre negatif
	// view = (t_mgam2i){cub->cam->look.x + SPACE * 5, cub->cam->look.y + SPACE * 5};
	
	// int	y;
	// int	x;
	// y = -1;
	// boucle final qui va tout dessiner de haut en bas
	// d'abord dessiner le ciel, puis le pixel correspondant a la texture en fonction de la distance a laquelle le rayon a ete envoye
	// puis dessiner le sol
	// while (++y < cub->data->height)
	// {
	//	lengthRay(cub, y)
	//	
	// 	x = -1;
	// 	while (++x < cub->data->width)
	// 		setpixel(cub->data, x, y, 0);
	// }
	miniMap(cub, cub->data);
	// breseline(cub, pos, view);
	dda(cub, pos, view);
	mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img, 0, 0);
}

int	wallHit(t_cub *cub, int x, int y)
{
	x = (x - cub->data->x_off) / SPACE;
	y = (y - cub->data->y_off) / SPACE;
	if ((x < 0 || x > cub->map->l) || (y < 0 || y > cub->map->L))
		return (1);
	if (cub->map->matrix[y][x] == '1')
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

// mlx_hook(cub->data->win, XK_w, (1L<<0), &press_w, cub);
// mlx_hook(cub->data->win, XK_w, (1L<<1), &release_w, cub);

// mlx_hook(cub->data->win, XK_s, (1L<<0), &press_s, cub);
// mlx_hook(cub->data->win, XK_s, (1L<<1), &release_s, cub);

// mlx_hook(cub->data->win, XK_a, (1L<<0), &press_a, cub);
// mlx_hook(cub->data->win, XK_a, (1L<<1), &release_a, cub);

// mlx_hook(cub->data->win, XK_d, (1L<<0), &press_d, cub);
// mlx_hook(cub->data->win, XK_d, (1L<<1), &release_d, cub);

// mlx_hook(cub->data->win, XK_Left, (1L<<0), &press_left, cub);
// mlx_hook(cub->data->win, XK_Left, (1L<<1), &release_left, cub);

// mlx_hook(cub->data->win, XK_Right, (1L<<0), &press_right, cub);
// mlx_hook(cub->data->win, XK_Right, (1L<<1), &release_right, cub);
