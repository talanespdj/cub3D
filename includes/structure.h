/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:42:20 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/07 09:42:11 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <stdlib.h>

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		l;
	int		r;
	int		q;
	int		up;
	int		down;
	int		tab;
	int		shift;
}		t_keys;

typedef struct s_txt
{
	void	*img;
	char	*addr;
	char	*name;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}		t_txt;

typedef struct s_cub
{
	struct s_map	*map;
	struct s_cam	*cam;
	struct s_data	*data;
	struct s_ray	*ray;
	struct s_txt	*txt[4];
	struct s_keys	keys;
	int				fd;
	int				lim;
	int				minimap;
	int				mmap;
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
	int		lar;
	int		lon;
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
	int			bppixel;
	int			line_length;
	int			x_off;
	int			y_off;
}			t_data;

#endif
