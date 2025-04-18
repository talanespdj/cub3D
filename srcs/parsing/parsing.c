/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:36:03 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 15:54:31 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static	void	retrieve_txt_floor_ceiling(t_cub *cub, char *name);

void	parse_map(t_cub *cub, char *name)
{
	char	*line;
	int		i;

	txtprocess(cub);
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
	cub->map->lar -= 1;
	close(cub->fd);
	i = cub->lim;
	cub->fd = open(name, O_RDONLY);
	line = gnl(cub->fd);
	while (line && --i > 0)
		next_line(cub, &line);
	free(line);
	mapping(cub, NULL);
}

static	void	def_lim(t_cub *cub)
{
	char	*line;
	int		x;

	cub->lim = 0;
	x = 0;
	line = gnl(cub->fd);
	while (line && x < 6)
	{
		if (!null_line(line))
			x++;
		next_line(cub, &line);
		cub->lim++;
	}
	if (!line)
		wgas(cub, "invalid map", NULL);
	while (line)
		next_line(cub, &line);
	close(cub->fd);
}

static	void	retrieve_txt_floor_ceiling(t_cub *cub, char *name)
{
	char	*line;
	int		x;

	def_lim(cub);
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

void	setlook(t_cub *cub, char cardinal)
{
	if (cub->lim == -1)
		cub->lim = 1;
	if (cardinal == 'N')
	{
		cub->cam->look = (t_mgam2f){0.0, -1.0};
		cub->ray->plane = (t_mgam2f){0.66, 0.0};
	}
	else if (cardinal == 'S')
	{
		cub->cam->look = (t_mgam2f){0.0, 1.0};
		cub->ray->plane = (t_mgam2f){-0.66, 0.0};
	}
	else if (cardinal == 'W')
	{
		cub->cam->look = (t_mgam2f){-1.0, 0.0};
		cub->ray->plane = (t_mgam2f){0.0, -0.66};
	}
	else if (cardinal == 'E')
	{
		cub->cam->look = (t_mgam2f){1.0, 0.0};
		cub->ray->plane = (t_mgam2f){0.0, 0.66};
	}
}

void	txtprocess(t_cub *cub)
{
	int		i;

	i = -1;
	while (++i < 4)
	{
		cub->txt[i] = malloc(sizeof(t_txt));
		if (!cub->txt[i])
			wgas(cub, "Textures", "malloc t_txt failed");
		cub->txt[i]->name = NULL;
		cub->txt[i]->img = NULL;
		cub->txt[i]->addr = NULL;
	}
}
