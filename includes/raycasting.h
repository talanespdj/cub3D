/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:31:26 by tespandj          #+#    #+#             */
/*   Updated: 2024/12/01 01:04:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef double		t_mgam2f	__attribute__((ext_vector_type(2)));
typedef int		t_mgam2i	__attribute__((ext_vector_type(2)));


typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2i	_2dPlayer;
	t_mgam2f	look;
	
	int	FOV;
}		t_cam;

typedef struct s_point
{
	int		x;
	int		y;
}		t_point;

typedef struct s_bsl
{
	int		dx;
	int		dy;
	int		dx1;
	int		dy1;
	int		px;
	int		py;
	int		x;
	int		y;
	int		xe;
	int		ye;
}			t_bsl;

void		raycast(t_cub *cub);

void		fill_win(t_cub *cub);

void		setpixel(t_data *data, int x, int y, int color);


/// @brief	save fdd bresenham line algorithm
void		breseline(t_cub *cub, t_point a, t_point b);
void		bslinit(t_bsl *t, t_point a, t_point b);
void		slto(t_cub *cub, t_bsl *t);
void		sbto(t_cub *cub, t_bsl *t);
int			tabs(int n);



void	draw_map(t_map *map, t_data *data);




/// @brief hook
int		press_w(t_cub *cub);
int		release_w(t_cub *cub);
int		press_a(t_cub *cub);
int		release_a(t_cub *cub);
int		press_s(t_cub *cub);
int		release_s(t_cub *cub);
int		press_d(t_cub *cub);
int		release_d(t_cub *cub);
int		press_left(t_cub *cub);
int		release_left(t_cub *cub);
int		press_right(t_cub *cub);
int		release_right(t_cub *cub);


#endif
