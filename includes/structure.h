/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:42:20 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/28 21:42:22 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <stdlib.h>

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	l;
	int	r;
	int	q;
	int	up;
	int	down;
}		t_keys;

typedef struct s_txt
{
	void	*img;
	char	*addr;
	char	*name;
	int	width;
	int	height;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
}		t_txt;

typedef struct s_cub
{
	struct s_map	*map;
	struct s_cam	*cam;
	struct s_data	*data;
	struct s_ray	*ray;
	t_keys			keys;
	t_txt			*txt[4];
	int				fd;
	int				lim;
}		t_cub;

typedef struct spt
{
	const char	*str;
	char		**split;
	char		c;
	int			nb_words;
	int			indic;
	int			len;
	int			op;
	int			i;
}			t_split;

typedef struct s_map
{
	char	**matrix;
	int		L;
	int		l;
	int		floor;
	int		ceiling;
}		t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			endian;
	int			bits_per_pixel;
	int			line_length;
	int			x_off;
	int			y_off;
}			t_data;

#endif
