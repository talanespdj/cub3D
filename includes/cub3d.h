/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:22:13 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 21:23:18 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structure.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>

# define BUFFER_SIZE 42

void	everyinit(t_cub *cub, char *map_name);

int	cub3d(struct s_cub *cub, char *name);

///// PARSING
void	parse_map(t_cub *cub, char *name);

void	textures(t_cub *cub);
int	texture_checking(t_cub *cub, char *file);
void	fill_textures(t_cub *cub, char *line);

void	FC_colors(t_cub *cub);


///// GNL
char	*gnl(int fd);
char	*org(char *str);
char	*save_static(char *str, int rv);
char	*add_str(char *s1, char *s2);

///// SPLIT
char	**split(char const *str, char c);

///// TLIB.c
int	tstrlen(char *str);
char	*tdup(char *str);
char	*tjoin(char *str, char *add);
int	tstrcmp(char *str, char *cmp);
int	tinstr(char *str, char *search);

///// UTILS.c
void	err_msg(t_cub *cub, char *arg, char *str);
void	wegotasplituation(struct spt x);
void	freend(t_cub *cub);
int	null_line(char *str);
void	fsplit(char **str);
void	free_map(t_cub *cub);
void	gnl_free(int fd);

void	print_params(t_cub *cub);

#endif
