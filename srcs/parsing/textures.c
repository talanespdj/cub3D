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

int	tinstr(char *str, char *search);

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
			if (tinstr(line, "NO") || tinstr(line, "SO")
				|| tinstr(line, "WE") || tinstr(line, "EA"))
				fill_textures(cub, line, 0, -1);
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

void	fill_textures(t_cub *cub, char *line, int i, int c)
{
	t_txt	*tmp;
	char	name[1000];

	while ((line[i] >= 8 && line[i] <= 12) || line[i] == ' ')
		++i;
	if (line[i] && line[i + 1] && line[i] == 'N' && line[i + 1] == 'O')
		tmp = cub->txt[NO];
	else if (line[i] && line[i + 1] && line[i] == 'S' && line[i + 1] == 'O')
		tmp = cub->txt[SO];
	else if (line[i] && line[i + 1] && line[i] == 'E' && line[i + 1] == 'A')
		tmp = cub->txt[EA];
	else if (line[i] && line[i + 1] && line[i] == 'W' && line[i + 1] == 'E')
		tmp = cub->txt[WE];
	i += 2;
	while ((line[i] >= 8 && line[i] <= 12) || line[i] == ' ')
		++i;
	while (line[i] && (!((line[i] >= 8 && line[i] <= 12) || line[i] == ' ')))
		name[++c] = line[i++];
	while (line[i] && ((line[i] >= 8 && line[i] <= 12) || line[i] == ' '))
		++i;
	if (line[i])
		wgas(cub, "texture name is not alone", NULL);
	name[++c] = '\0';
	tmp->name = tdup(name);
}

int	tinstr(char *str, char *search)
{
	int	i;
	int	r;

	i = -1;
	if (!str || !search)
		return (0);
	while (str[++i])
	{
		if (str[i] == search[0])
		{
			r = 0;
			while (search[r] && str[i + r] && search[r] == str[i + r])
				r++;
			if (!search[r])
				return (1);
		}
	}
	return (0);
}
