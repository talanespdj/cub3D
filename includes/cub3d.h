/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:22:13 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/07 09:38:22 by tespandj         ###   ########.fr       */
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
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define BUFFER_SIZE 42

typedef struct s_ray	t_ray;

int				cub3d(t_cub *cub, t_data *data);
int				looping(t_cub *cub);

void			everyinit(t_cub *cub, char *map_name);

void			mapinit(t_cub *cub, char *name);
void			datainit(t_cub *cub);
void			caminit(t_cub *cub);
void			rayinit(t_ray *ray);
void			txtinit(t_cub *cub);

void			parse_map(t_cub *cub, char *name);
void			txtprocess(t_cub *cub);
void			setlook(t_cub *cub, char cardinal);

void			next_line(t_cub *cub, char **line);
bool			valid_char(char c, int indic);
void			textures(t_cub *cub, t_txt **txt);
void			checktxt(t_cub *cub);
void			fill_textures(t_cub *cub, char *line, int i, int c);

void			fccolors(t_cub *cub);
void			fill_colors(t_cub *cub, char *line, int *color);

void			length_map(t_cub *cub);
void			mapping(t_cub *cub, char *line);

char			*gnl(int fd);
char			*org(char *str);
char			*save_static(char *str, int rv);
char			*add_str(char *s1, char *s2);

char			**split(char const *str, char c);

int				tstrlen(char *str);
char			*tdup(char *str);
char			*tjoin(char *str, char *add);
int				tstrcmp(char *str, char *cmp);

bool			validcase(char **matrix, int width, int x, int y);
bool			validmap(t_cub *cub, char **matrix);
char			*erase_new_line(char *str);
int				null_line(char *str);
int				null_linev2(char *str);

void			wgas(t_cub *cub, char *arg, char *str);
void			wegotasplituation(struct spt x);
void			freend(t_cub *cub);
void			fsplit(char **str);

int				end_win(t_cub *cub);

void			movement(t_cub *cub);
void			forward(t_cub *cub, double ms);
void			backward(t_cub *cub, double ms);
void			right(t_cub *cub, double ms);
void			left(t_cub *cub, double ms);

int				press(int key, t_cub *cub);
int				release(int key, t_cub *cub);

#endif
