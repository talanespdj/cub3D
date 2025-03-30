/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 03:45:31 by tespandj          #+#    #+#             */
/*   Updated: 2025/03/30 03:45:34 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

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
	int		i;

	i = -1;
	line = malloc(sizeof(char) * tstrlen(str));
	if (!line)
		return (NULL);
	while (str && str[++i] && str[i + 1])
		line[i] = str[i];
	line[i] = '\0';
	return (line);
}

int	end_win(t_cub *cub)
{
	mlx_destroy_image(cub->data->mlx, cub->data->img);
	mlx_destroy_window(cub->data->mlx, cub->data->win);
	mlx_destroy_display(cub->data->mlx);
	free(cub->data->mlx);
	freend(cub);
	exit(0);
}
