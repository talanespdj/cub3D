/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:36:03 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 03:36:05 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	print_params(t_cub *cub)
{
	if (cub->map->NO)
		printf("cub->map->NO // %s\n", cub->map->NO);
	if (cub->map->SO)
		printf("cub->map->SO // %s\n", cub->map->SO);
	if (cub->map->WE)
		printf("cub->map->WE // %s\n", cub->map->WE);
	if (cub->map->EA)
		printf("cub->map->EA // %s\n", cub->map->EA);
}

void	parse_map(t_cub *cub, char *name)
{
	if (access(name, F_OK))
		err_msg(cub, name, "File doesn't exist");
	else if (access(name, R_OK))
		err_msg(cub, name, "No permission to read the map");
	cub->fd = open(name, O_RDONLY);
	if (cub->fd == -1)
		err_msg(cub, name, "Failed to open the map");
	textures(cub);
	FC_colors(cub);
}
