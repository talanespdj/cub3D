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
#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define M_PI 3.14159265358979323846
# define SPACE 64
# define RATIO_PLAYER 8
# define RATIO_MOVE 4

# define MAP_VOID 0x353831
// # define MAP_WALL 0x090C08
# define MAP_WALL 0xFF0000
# define MAP_PLAYER 0x474056

# define MAP_SKY 0x778BF0
# define MAP_FLOOR 0x7C7C7C

# define MOVESPEED 0.002
# define ROTATESPEED 0.002

typedef double	t_mgam2f __attribute__((ext_vector_type(2)));
typedef int		t_mgam2i __attribute__((ext_vector_type(2)));

typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2f	look;
}		t_cam;

typedef struct s_ray
{
	t_mgam2i	map;
	t_mgam2f	ray;
	t_mgam2f	plane;
	t_mgam2f	sidedist;
	t_mgam2f	deltadist;
	t_mgam2i	step;
	double		camerax;
	double		perpwalldist;
	int			x;
	int			raylength;
	int			whichside;
	int			startp;
	int			endp;
}		t_ray;

void		raycast(t_cub *cub);
void		setpixel(t_data *data, int x, int y, int color);

void		minimap(t_cub *cub, t_data *data);
int			wallhit(t_cub *cub, double x, double y);

void		dda(t_cub *cub, t_ray *ray);
void		verticaline(t_cub *cub, t_ray *ray, int x);

/// @brief hook
void		lookmove(t_ray *ray, t_cam *cam, int key);
int			press(int key, t_cub *cub);
int			release(int key, t_cub *cub);

#endif
