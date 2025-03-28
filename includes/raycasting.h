/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:31:26 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/21 23:41:35 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define MMAP 16
# define MAP_VOID 0x353831
// # define MAP_WALL 0x090C08
# define MAP_WALL 0xFF0000
# define MAP_PLAYER 0x474056

# define MAP_SKY 0x778BF0
# define MAP_FLOOR 0x7C7C7C

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define MOVESPEED 0.02
# define ROTATESPEED 0.02

typedef double	t_mgam2f __attribute__((ext_vector_type(2)));
typedef int		t_mgam2i __attribute__((ext_vector_type(2)));

typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2f	look;
	int		mouse_x;
	int		mouse_y;
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

void		raycast(t_cub *cub, t_ray *ray);
void		dda(t_cub *cub, t_ray *ray);
void		texture_pixel(t_cub *cub, t_ray *ray);


void		setpixel(t_data *data, int x, int y, int color);

void		minimap(t_cub *cub, char **matrix);
int			wallhit(t_cub *cub, double x, double y);

/// @brief hook
void		lookmove(t_ray *ray, t_cam *cam, int key);
int			press(int key, t_cub *cub);
int			release(int key, t_cub *cub);
int			mousemotion(t_cub *cub);

#endif
