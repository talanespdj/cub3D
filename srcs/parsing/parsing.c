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

static	void	retrieve_txt_floor_ceiling(t_cub *cub, char *name);

void	parse_map(t_cub *cub, char *name)
{
	char	*line;
	int		i;

	i = -1;
	if (access(name, F_OK))
		wgas(cub, name, "File doesn't exist");
	else if (access(name, R_OK))
		wgas(cub, name, "No permission to read the map");
	cub->fd = open(name, O_RDONLY);
	if (cub->fd == -1)
		wgas(cub, name, "Failed to open the map");
	while (++i < 4)
	{
		cub->txt[i] = malloc(sizeof(t_txt));
		if (!cub->txt[i])
			wgas(cub, "Textures", "malloc t_txt failed");
		cub->txt[i]->name = NULL;
		cub->txt[i]->img = NULL;
		cub->txt[i]->addr = NULL;
	}
	retrieve_txt_floor_ceiling(cub, name);
	textures(cub, cub->txt); 
	fccolors(cub);
	i = cub->lim;
	cub->fd = open(name, O_RDONLY);
	line = gnl(cub->fd);
	while (line && --i > 0)
		next_line(cub, &line);
	free(line);
	fsplit(cub->map->matrix);
	cub->map->matrix = NULL;
	length_map(cub);
	i = cub->lim;
	cub->fd = open(name, O_RDONLY);
	line = gnl(cub->fd);
	while (line && --i > 0)
		next_line(cub, &line);
	free(line);
	mapping(cub, NULL);
}

static	void	retrieve_txt_floor_ceiling(t_cub *cub, char *name)
{
	char	*line;
	int		x;

	cub->lim = 0;
	line = gnl(cub->fd);
	while (line)
	{
		x = 0;
		while (line[x] && valid_char(line[x], 0))
			x++;
		if ((!line[x] || !line[x + 1]) && !null_line(line))
			break ;
		next_line(cub, &line);
		cub->lim++; // stocker ou commence la map
	}
	while (line)
		next_line(cub, &line);
	close(cub->fd);
	cub->map->matrix = malloc(sizeof(char *) * (cub->lim + 1));
	if (!cub->map->matrix)
		wgas(cub, "retrieve_txt_floor_ceiling", NULL);
	cub->fd = open(name, O_RDONLY);
	x = -1;
	while (++x < cub->lim)
		cub->map->matrix[x] = gnl(cub->fd);
	cub->map->matrix[x] = NULL;
	line = gnl(cub->fd);
	while (line)
		next_line(cub, &line);
	close(cub->fd);
}