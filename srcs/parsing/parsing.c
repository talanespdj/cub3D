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

void	parse_map(t_cub *cub, char *name)
{
	int	i;

	i = -1;
	if (access(name, F_OK))
		wgas(cub, name, "File doesn't exist");
	else if (access(name, R_OK))
		wgas(cub, name, "No permission to read the map");
	cub->fd = open(name, O_RDONLY);
	if (cub->fd == -1)
		wgas(cub, name, "Failed to open the map");
	*cub->txt = malloc(sizeof(t_txt *));
	while (++i < 4)
	{
		cub->txt[i] = malloc(sizeof(t_txt));
		if (!cub->txt[i])
			wgas(cub, "Textures", "malloc t_txt failed");
		cub->txt[i]->name = NULL;
	}
	textures(cub);
	fccolors(cub);
	mapping(cub, NULL, NULL);
}
