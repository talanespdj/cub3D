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
#include "../../includes/cub3d.h"

#ifndef RAYCASTING_H
# define RAYCASTING_H

# define M_PI 3.14159265358979323846
# define SPACE 64
# define ratio_player SPACE / 2
# define dist_player_move ratio_player / 4

# define map_void 0xAEB8FE
# define map_wall 0x27187E
# define map_player 0xAEB8FE

typedef double		t_mgam2f	__attribute__((ext_vector_type(2)));
typedef int		t_mgam2i	__attribute__((ext_vector_type(2)));

typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2i	_2dPlayer;
	t_mgam2f	look;
	t_mgam2f	view_angle; // a initialiser en fonction de N S E O sur la map et de la position du joueur sur la map


	int	FOV;
}		t_cam;

    

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
void		setpixel(t_data *data, int x, int y, int color);

void		miniMap(t_cub *cub, t_data *data);
int		wallHit(t_cub *cub, int x, int y);


/// @brief bientot plus besoin 
void		breseline(t_cub *cub, t_mgam2i a, t_mgam2i b);
void		bslinit(t_bsl *t, t_mgam2i a, t_mgam2i b);
void		slto(t_cub *cub, t_bsl *t);
void		sbto(t_cub *cub, t_bsl *t);
int			tabs(int n);

// t_mgam2i	_2point_slope(t_mgam2f a, t_mgam2f b);
int	_2point_slope(t_mgam2f a, t_mgam2f b);
void	dda(t_cub *cub, t_mgam2f a, t_mgam2f b);


void	lookMove(t_cam *cam, int key);
int	valid_move(int key, t_cub *cub);
int	keyPressed(int key, t_cub *cub);

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
