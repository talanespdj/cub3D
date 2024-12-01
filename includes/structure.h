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

typedef struct s_cub
{
	struct s_map	*map;
	struct s_cam	*cam;
	struct s_data	*data;
	char		*map_name;
	int			fd;
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

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;

}		t_rgb;

typedef struct s_map
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_rgb	*F;
	t_rgb	*C;
	char	**matrix;
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
}			t_data;

#endif
