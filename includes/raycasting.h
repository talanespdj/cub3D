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

# define M_PI 3.14159265358979323846
# define SPACE 64
# define ratio_player SPACE / 2
# define dist_player_move ratio_player / 4
# define RATIO_MOVE 4

# define map_void 0x353831
# define map_wall 0x090C08
# define map_player 0x474056

# define moveSpeed 0.05
# define rotateSpeed 0.05

typedef double		t_mgam2f	__attribute__((ext_vector_type(2)));
typedef int		t_mgam2i	__attribute__((ext_vector_type(2)));

typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2f	look;
	t_mgam2f	oldlook;
	t_mgam2f	time;
	int		FOV;


}		t_cam;

typedef	struct s_ray
{
	t_mgam2i	map;
	t_mgam2f	ray;
	t_mgam2f	plane;
	t_mgam2f	sideDist;
	t_mgam2f	deltaDist;
	int		stepx;
	int		stepy;
	double		cameraX;
	double		perpWallDist;
}		t_ray;

void		raycast(t_cub *cub);
void		setpixel(t_data *data, int x, int y, int color);

void		miniMap(t_cub *cub, t_data *data);
double		lengthRay(t_cub *cub, t_mgam2f startP, t_mgam2f endP);
int		wallHit(t_cub *cub, int x, int y);


// t_mgam2i	_2point_slope(t_mgam2f a, t_mgam2f b);
int	_2point_slope(t_mgam2f a, t_mgam2f b);
// void	dda(t_cub *cub, t_mgam2f a, t_mgam2f b);
void	dda(t_cub *cub, t_mgam2i a, t_mgam2i b);




/// @brief hook
int	press(int key, t_cub *cub);
int	release(int key, t_cub *cub);
void	lookMove(t_cam *cam, int key);

#endif
