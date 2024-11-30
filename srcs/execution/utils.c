/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:05:10 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 01:05:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	err_msg(t_cub *cub, char *arg, char *str)
{
	if (arg)
		printf("%s", arg);
	if (str)
		printf(": %s", str);
	printf("\n");
	freend(cub);
	if (cub->fd > 0)
		close(cub->fd);
	exit(1);
}

void	wegotasplituation(struct spt x)
{
	int	i;

	i = 0;
	while (x.split[i] && i <= x.op)
	{
		free(x.split[i]);
		i++;
	}
	free(x.split);
}

void	free_map(t_cub *cub)
{
	gnl_free(cub->fd);
	if (cub->map)
	{
		if (cub->map->NO)
			free(cub->map->NO);
		if (cub->map->SO)
			free(cub->map->SO);
		if (cub->map->EA)
			free(cub->map->EA);
		if (cub->map->WE)
			free(cub->map->WE);
		if (cub->map->F)
			free(cub->map->F);
		if (cub->map->C)
			free(cub->map->C);
		if (cub->map->matrix)
			fsplit(cub->map->matrix);
	}
	free(cub->map);
}

void	freend(t_cub *cub)
{
	free_map(cub);
	if (cub->map_name)
		free(cub->map_name);
}

int	null_line(char *str)
{
	int	i;
	
	i = -1;
	while (str && str[++i])
		if (!((str[i] >= 8 && str[i] <= 12) || str[i] == ' '))
			return (0);
	return (1);
}

void	fsplit(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
}

void	gnl_free(int fd)
{
	char	*line;

	line = gnl(fd);
	while (line)
	{
		free(line);
		line = gnl(fd);
	}
	if (fd > 0)
		close(fd);
}

char	*erase_new_line(char *str)
{
	char	*line;
	int	i;

	i = -1;
	line = malloc(sizeof(char) * tstrlen(str));
	if (!line)
		return (NULL);
	while (str && str[++i] && str[i + 1])
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}