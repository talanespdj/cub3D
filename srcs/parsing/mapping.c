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

void	mapping(t_cub *cub)
{
	char	*line;
	char	*save;

	save = NULL;
	line = gnl(cub->fd);
	while (null_line(line))
	{
		free(line);
		line = gnl(cub->fd);
	}
	while (line)
	{
		while (null_line(line))
		{
			free(line);
			line = gnl(cub->fd);
			if (!null_line(line))
			{
				free(line);
				free(save);
				err_msg(cub, "mapping",
					"Map is cut in some pieces i dont like it");
			}
		}
		save = tjoin(save, line);
		free(line);
		line = gnl(cub->fd);
	}
	cub->map->matrix = split(save, '\n');
	free(save);
	if (!cub->map->matrix)
		err_msg(cub, "split matrix failed", NULL);
}
