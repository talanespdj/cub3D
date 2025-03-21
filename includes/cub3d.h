/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:22:13 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/30 06:55:17 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "structure.h"
# include "raycasting.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define BUFFER_SIZE 42

typedef struct s_ray	t_ray;

long long int	atolli(char *str);

int				cub3d(struct s_cub *cub);
int				looping(t_cub *cub);

void			everyinit(t_cub *cub, char *map_name);

void			mapinit(t_cub *cub);
void			datainit(t_cub *cub);
void			caminit(t_cub *cub);
void			rayinit(t_ray *ray);

void			parse_map(t_cub *cub, char *name);

void			textures(t_cub *cub);
int				texture_checking(t_cub *cub, char *file);
void			fill_textures(t_cub *cub, char *line);

void			fccolors(t_cub *cub);
void			fill_floor(t_cub *cub, char *line);
void			fill_ceiling(t_cub *cub, char *line);

void			mapping(t_cub *cub, char *save, char *line);
void			build_matrix(t_cub *cub, char *save, char *line);

char			*gnl(int fd);
char			*org(char *str);
char			*save_static(char *str, int rv);
char			*add_str(char *s1, char *s2);

char			**split(char const *str, char c);

int				tstrlen(char *str);
char			*tdup(char *str);
char			*tjoin(char *str, char *add);
int				tstrcmp(char *str, char *cmp);
int				tinstr(char *str, char *search);

int				valid_lli(long long int nt, char c, int sign, int situation);
int				check_lli(char *str);
char			*erase_new_line(char *str);
int				null_line(char *str);

void			wgas(t_cub *cub, char *arg, char *str);
void			wegotasplituation(struct spt x);
void			freend(t_cub *cub);
void			fsplit(char **str);
void			free_map(t_cub *cub);
void			gnl_free(int fd);
int				end_win(t_cub *cub);

/////////////////////

void			movement(t_cub *cub);
int				press(int key, t_cub *cub);
int				release(int key, t_cub *cub);

#endif
