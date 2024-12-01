
#include "../../includes/cub3d.h"

int	key_press(int key, t_cub *cub)
{
	if (key == XK_w || key == XK_Up)
		cub->cam->y -= 10;
	if (key == XK_s || key == XK_Down)
		cub->cam->y += 10;
	if (key == XK_a || key == XK_Left)
		cub->cam->x -= 10;
	if (key == XK_d || key == XK_Right)
		cub->cam->x += 10;
	if (key == XK_Escape)
		end_win(cub);
	raycast(cub);
	return (0);
}
