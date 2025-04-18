/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:31:26 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/07 09:40:21 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define MMAP 16

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define MS 0.03
# define ROTATESPEED 0.015

typedef double	t_mgam2f __attribute__((ext_vector_type(2)));
typedef int		t_mgam2i __attribute__((ext_vector_type(2)));

typedef struct s_cam
{
	t_mgam2f	player_pos;
	t_mgam2f	look;
}		t_cam;

typedef struct s_ray
{
	t_txt		*txt;
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
	int			texx;
}		t_ray;

void		raycast(t_cub *cub, t_ray *ray);

void		dda(t_cub *cub, t_ray *ray);
t_txt		*cardinalstxt(t_cub *cub, t_ray *ray);
void		xpos(t_cub *cub, t_ray *ray);
void		txt_pixel(t_cub *cub, t_ray *ray);

void		setpixel(t_data *data, int x, int y, int color);
uint		getpixel(t_txt *txt, int x, int y);

void		minimap(t_cub *cub, char **matrix);
int			wallhit(t_cub *cub, double x, double y);

/// @brief hook
void		lookmove(t_ray *ray, t_cam *cam, int key);
int			press(int key, t_cub *cub);
int			release(int key, t_cub *cub);

#endif
