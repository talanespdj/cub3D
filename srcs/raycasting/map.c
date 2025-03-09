#include "../../includes/cub3d.h"

int	return_color(char c)
{
	if (c == '0')
		return map_void;
	if (c == '1')
		return map_wall;
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return 0xFF8600; // former : 0xFF8600
	return map_player; //couleur pour joueurn
}

void	miniMap(t_cub *cub, t_data *data)
{
	t_mgam2i pos;
	int	i;
	size_t	j;
	int	size;
	int	row;
	int	col;

	i = -1;
	size = cub->map->L * (cub->map->l - 1);
	pos = (t_mgam2i){cub->cam->player_pos.x, cub->cam->player_pos.y};
	while (++i < size)
	{
		j = -1;
		row = i / (cub->map->l - 1); // FIXED: Correct row calculation
		col = i % (cub->map->l - 1); // FIXED: Correct column calculation
		while (++j < (SPACE * SPACE))
			setpixel(data, (col * SPACE + (j / SPACE)) + data->x_off,
				 (row * SPACE + (j % SPACE)) + data->y_off, return_color(cub->map->matrix[row][col]));
	}
	i = -1;
	while (++i < SPACE / 4)
	{
		j = -1;
		while (++j < SPACE / 4)
			setpixel(cub->data, pos.x + i, pos.y + j, 0xFF0000);
	}
}