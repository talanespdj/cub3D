/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:21:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 21:26:35 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"

void	everyinit(t_cub *cub, char *name)
{
	cub->fd = -1;
	cub->lim = -1;
	cub->minimap = 1;
	mapinit(cub, name);
	datainit(cub);
	cub->ray = malloc(sizeof(t_ray));
	if (!cub->ray)
		wgas(cub, "malloc ray failed", NULL);
	rayinit(cub->ray);
	cub->cam = malloc(sizeof(t_cam));
	if (!cub->cam)
		wgas(cub, "malloc cam failed", NULL);
	cub->cam->look = (t_mgam2f){0.0, 0.0};
	cub->cam->player_pos = (t_mgam2f){0.0, 0.0};
	cub->lim = -1;
	caminit(cub);
	txtinit(cub);
}

static	int	valid_name(char *name)
{
	int	i;

	i = 0;
	while (name && name[i])
		i++;
	if (i > 4 && (name[i - 1] == 'b' && name[i - 2] == 'u'
			&& name[i - 3] == 'c' && name[i - 4] == '.'))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	static t_cub	cub = {0};

	if (argc != 2 || !valid_name(argv[1]))
		printf("There must be a map (.cub) in argument\n");
	else
	{
		everyinit(&cub, argv[1]);
		cub3d(&cub, cub.data);
	}
	return (0);
}
