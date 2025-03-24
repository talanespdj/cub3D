#include "../../includes/cub3d.h"

int	mmap_color(char c)
{
	if (c == '0')
		return (MAP_VOID);
	else if (c == '1')
		return (MAP_WALL);
	return (0);
}

void	minimap(t_cub *cub, char **matrix)
{
	int	x;
	int	y;
	int	r;
	int	t;
	int	color;

	y = -1;
	/// print the whole mMap
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (matrix[y][x] == '0' || matrix[y][x] == '1')
			{
				color = mmap_color(matrix[y][x]);
				r = -1;
				while (++r < MMAP)
				{
					t = -1;
					while (++t < MMAP)
						setpixel(cub->data, x * MMAP + r, y * MMAP + t, color);
				}
			}
		}
	}

	// map qui bouge en fonction de la pos du joueur

	// t_mgam2f	pos;
	// t_mgam2f	x_limits;
	// t_mgam2f	y_limits;


	// pos = cub->cam->player_pos;
	// x_limits.x = pos.x - 4 > 0 ? pos.x - 4 : 0;
	// x_limits.y = pos.x + 4 < cub->map->l ? pos.x + 4 : cub->map->l;
	// y_limits.x = pos.x - 4 > 0 ? pos.x - 4 : 0;
	// y_limits.y = pos.x + 4 < cub->map->l ? pos.x + 4 : cub->map->L;

	// printf("x_limits = {%f, %f}\n", x_limits.x, x_limits.y); // d'où je dois aller horizontalement dans la map 
	// printf("y_limits = {%f, %f}\n", y_limits.x, y_limits.y); // pareil verticalement

	// while (y_limits.x < (y_limits.y))
	// {
	// 	x = (int)x_limits.x - 1;
	// 	while (++x < (x_limits.y))
	// 		setpixel(cub->data, term
	// 			x, (int)y_limits.x, mmap_color(matrix[(int)y_limits.x][x]));
	// 	y_limits.x++;
	// }
}
