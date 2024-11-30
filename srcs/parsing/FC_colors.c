/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FC_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 04:48:51 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 04:49:04 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static	int	rgb_check(char *str);

void	FC_colors(t_cub *cub)
{
	char	*line;

	line = gnl(cub->fd);
	while (line && (!cub->map->F || !cub->map->C))
	{
		if (!null_line(line))
		{
			if (line[0] && line[0] == 'F')
				fill_floor(cub, line);
			else if (line[0] && line[0] == 'C')
				fill_ceiling(cub, line);
			else
				break ;
		}
		free(line);
		if ((cub->map->F && cub->map->C))
			break ; 
		line = gnl(cub->fd);
	}
	if (!cub->map->F || !cub->map->C)
		err_msg(cub, cub->map_name,
			"First lines should contain address Floor and ceiling value");

}

void	fill_floor(t_cub *cub, char *line)
{
	char	**rgb;
	char	*floor;

	rgb = split(line, ' ');
	if (tstrcmp(rgb[0], "F") || !rgb[1])
	{
		fsplit(rgb);
		err_msg(cub, "First lines should contain Floor and Ceiling RGB colors\n", NULL);
	}
	floor = erase_new_line(rgb[1]);
	fsplit(rgb);
	rgb = split(floor, ',');
	free(floor);
	if (!rgb || (!(rgb[0] && rgb[1] && rgb[2]))
		|| (!rgb_check(rgb[0]) || !rgb_check(rgb[1]) || !rgb_check(rgb[2])))
	{
		fsplit(rgb);
		err_msg(cub, "floor", "invalid rgb value");
	}
	cub->map->F = malloc(sizeof(t_rgb));
	if (!cub->map->F)
		return (freend(cub));
	cub->map->F->r = atolli(rgb[0]);
	cub->map->F->g = atolli(rgb[1]);
	cub->map->F->b = atolli(rgb[2]);
	fsplit(rgb);
}

void	fill_ceiling(t_cub *cub, char *line)
{
	char	**rgb;
	char	*ceiling;

	rgb = split(line, ' ');
	if (!rgb || tstrcmp(rgb[0], "C") || !rgb[1])
	{
		fsplit(rgb);
		err_msg(cub, "First lines should contain floor and Ceiling RGB colors\n", NULL);
	}
	ceiling = erase_new_line(rgb[1]);
	fsplit(rgb);
	rgb = split(ceiling, ',');
	free(ceiling);
	if (!rgb || (!(rgb[0] && rgb[1] && rgb[2]))
		|| (!rgb_check(rgb[0]) || !rgb_check(rgb[1]) || !rgb_check(rgb[2])))
	{
		fsplit(rgb);
		err_msg(cub, "ceiling", "invalid rgb value");
	}
	cub->map->C = malloc(sizeof(t_rgb));
	if (!cub->map->C)
		return (freend(cub));
	cub->map->C->r = atolli(rgb[0]);
	cub->map->C->g = atolli(rgb[1]);
	cub->map->C->b = atolli(rgb[2]);
	fsplit(rgb);
}

static	int	rgb_check(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i] && str[i + 1])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (!check_lli(str) || (atolli(str) < 0 || atolli(str) > 255))
		return (0);
	return (1);
}