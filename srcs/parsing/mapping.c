/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:14:13 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/30 03:14:31 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static	void	next_line(t_cub *cub, char **line)
{
	free(*line);
	*line = gnl(cub->fd);
}

void	mapping(t_cub *cub)
{
	build_matrix(cub, NULL, NULL);
	
}

void	build_matrix(t_cub *cub, char *save, char *line)
{
	line = gnl(cub->fd);
	while (null_line(line))
		next_line(cub, &line);
	while (line)
	{
		while (null_line(line))
		{
			next_line(cub, &line);
			if (!null_line(line))
			{
				free(line);
				free(save);
				wgas(cub, "mapping",
					"Map is cut in some pieces i dont like it");
			}
		}
		save = tjoin(save, line);
		next_line(cub, &line);
	}
	cub->map->matrix = split(save, '\n');
	free(save);
	if (!cub->map->matrix)
		wgas(cub, "split matrix failed", NULL);
	if (cub->fd > 0)
		close(cub->fd);
}