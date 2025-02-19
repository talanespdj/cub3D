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
	int	i;

	i = -1;
	printf("\n");
	if (cub->map->NO)
		printf("\tNO %s\n", cub->map->NO);
	if (cub->map->SO)
		printf("\tSO %s\n", cub->map->SO);
	if (cub->map->WE)
		printf("\tWE %s\n", cub->map->WE);
	if (cub->map->EA)
		printf("\tEA %s\n", cub->map->EA);
	if (cub->map->F)
		printf("\tFloor : %d,%d,%d\n", cub->map->F->r, cub->map->F->g, cub->map->F->b);
	if (cub->map->C)
		printf("\tCeiling : %d,%d,%d\n", cub->map->C->r, cub->map->C->g, cub->map->C->b);
	printf("\n");
	printf("\n");
	if (cub->map->matrix)
		while (cub->map->matrix[++i])
			printf("%s\n", cub->map->matrix[i]);
	printf("\n");
}

void		parse_map(t_cub *cub, char *name)
{
	if (access(name, F_OK))
		wgas(cub, name, "File doesn't exist");
	else if (access(name, R_OK))
		wgas(cub, name, "No permission to read the map");
	cub->fd = open(name, O_RDONLY);
	if (cub->fd == -1)
		wgas(cub, name, "Failed to open the map");
	textures(cub);
	FC_colors(cub);
	mapping(cub);
	print_params(cub);
}
