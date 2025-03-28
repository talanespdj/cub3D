/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:41:38 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 03:41:40 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	textures(t_cub *cub)
{
	char	*line;

	line = gnl(cub->fd);
	while (line && (!cub->txt[NO]->name || !cub->txt[SO]->name || !cub->txt[EA]->name || !cub->txt[WE]->name))
	{
		if (!null_line(line))
		{
			if (line[0] && line[1] && line[0] == 'N' && line[1] == 'O')
				fill_textures(cub, line);
			else if (line[0] && line[1] && line[0] == 'S' && line[1] == 'O')
				fill_textures(cub, line);
			else if (line[0] && line[1] && line[0] == 'W' && line[1] == 'E')
				fill_textures(cub, line);
			else if (line[0] && line[1] && line[0] == 'E' && line[1] == 'A')
				fill_textures(cub, line);
			else 
				break ;
		}
		free(line);
		if (cub->txt[NO]->name && cub->txt[SO]->name && cub->txt[EA]->name && cub->txt[WE]->name)
			break ;
		line = gnl(cub->fd);
	}
	if (!cub->txt[NO]->name && !cub->txt[SO]->name && !cub->txt[EA]->name && !cub->txt[WE]->name)
		wgas(cub, "textures",
			"First lines should contain address of NE SO WE EA textures");
}

int	texture_checking(t_cub *cub, char *file)
{
	if (file && file[0] && file[1] && (file[0] != '.' || file[1] != '/'))
		wgas(cub, file, "Should be a relative path");
	else if (access(file, F_OK))
		wgas(cub, file, "File doesn't exist");
	else if (access(file, R_OK))
		wgas(cub, file, "No permission to read the texture");
	return (1);
}

void	fill_textures(t_cub *cub, char *line)
{
	char	**inf;

	inf = split(line, ' ');
	if (!inf)
		wgas(cub, "Textures", "Couldn't split line");
	if (inf && inf[0] && inf[1])
	{
		if (!tstrcmp(inf[0], "NO"))
			cub->txt[NO]->name = erase_new_line(inf[1]);
			// cub->map->north = erase_new_line(inf[1]);
		if (!tstrcmp(inf[0], "SO"))
			cub->txt[SO]->name = erase_new_line(inf[1]);
			// cub->map->south = erase_new_line(inf[1]);
		if (!tstrcmp(inf[0], "WE"))
			cub->txt[WE]->name = erase_new_line(inf[1]);
			// cub->map->west = erase_new_line(inf[1]);
		if (!tstrcmp(inf[0], "EA"))
			cub->txt[EA]->name = erase_new_line(inf[1]);
			// cub->map->east = erase_new_line(inf[1]);
	}
	fsplit(inf);
}
