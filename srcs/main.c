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
	t_cub	cub;

	if (argc != 2 || !valid_name(argv[1]))
	{
		printf("There must be a map (.cub) in argument\n");
		return (1);
	}
	cub3d(&cub, argv[1]);
	freend(&cub);
	return (0);
}
