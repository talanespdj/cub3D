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

void	textures(t_cub *cub, t_txt **txt)
{
	char	*line;
	int		i;

	i = 0;
	line = cub->map->matrix[i];
	while (line && (!txt[NO]->name || !txt[SO]->name
			|| !txt[EA]->name || !txt[WE]->name))
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
		}
		if (txt[NO]->name && txt[SO]->name && txt[EA]->name && txt[WE]->name)
			break ;
		line = cub->map->matrix[++i];
	}
	checktxt(cub);
}

void	checktxt(t_cub *cub)
{
	char	*file;
	int		i;

	i = -1;
	while (cub->txt[++i])
	{
		file = cub->txt[i]->name;
		if (!file)
			wgas(cub, "texture address missing", NULL);
		if (file && file[0] && file[1] && (file[0] != '.' || file[1] != '/'))
			wgas(cub, file, "Should be a relative path");
		else if (access(file, F_OK))
			wgas(cub, file, "File doesn't exist");
		else if (access(file, R_OK))
			wgas(cub, file, "No permission to read the texture");
	}
}

void	fill_textures(t_cub *cub, char *line)
{
	char	**inf;
	char	*str;

	inf = split(line, '\n');
	if (!inf)
		wgas(cub, "first split", NULL);
	str = tdup(inf[0]);
	fsplit(inf);
	inf = NULL;
	inf = split(str, ' ');
	free(str);
	if (!inf || (inf[0] && inf[1] && inf[2]))
		wgas(cub, inf[2], "texture name has to be on its own");
	if (inf[0] && inf[1])
	{
		if (!tstrcmp(inf[0], "NO"))
			cub->txt[NO]->name = tdup(inf[1]);
		if (!tstrcmp(inf[0], "SO"))
			cub->txt[SO]->name = tdup(inf[1]);
		if (!tstrcmp(inf[0], "WE"))
			cub->txt[WE]->name = tdup(inf[1]);
		if (!tstrcmp(inf[0], "EA"))
			cub->txt[EA]->name = tdup(inf[1]);
	}
	fsplit(inf);
}
