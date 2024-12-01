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

typedef struct s_cam
{
	float	x;
	float	y;
	int	FOV;
}		t_cam;

void	raycast(t_cub *cub);

void	fill_win(t_cub *cub);
void	aff_cam(t_cub *cub);
void	aff_map(t_cub *cub);

void	reset_cub(t_cub *cub);
void	setblock(t_cub *cub, int x, int y, int color);
void	setpixel(t_data *data, int x, int y, int color);

#endif
