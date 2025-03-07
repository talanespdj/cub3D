
#include "../../includes/cub3d.h"

/// faire les rayons 10 cases par 10 cases jusqu'a ce que ca hit un mur


void	lookMove(t_mgam2f *look)
{
	(void)look;
	
}

int	key_press(int key, t_cub *cub)
{
	if (key == XK_w) {
		cub->cam->player_pos -= (t_mgam2f){0, 10.1};
		cub->cam->look -= (t_mgam2f){0, 10.1};
	}
	if (key == XK_s) {
		cub->cam->player_pos += (t_mgam2f){0, 10.1};
		cub->cam->look += (t_mgam2f){0, 10.1};
	}
	if (key == XK_a) {
		cub->cam->player_pos -= (t_mgam2f){10.1, 0};
		cub->cam->look -= (t_mgam2f){10.1, 0};
	}
	if (key == XK_d) {
		cub->cam->player_pos += (t_mgam2f){10.1, 0};
		cub->cam->look += (t_mgam2f){10.1, 0};
	}
	if (key == XK_Left || key == XK_Right) {
		// cub->cam->look += (t_mgam2f){0, 0.00159};
		cub->cam->look += (t_mgam2f){0, 10.00159};
		lookMove(&cub->cam->look);
	}
	if (key == XK_Escape)
		end_win(cub);
	raycast(cub);
	return (0);
}

void	press(t_cub *cub) {
	
}


void	release(t_cub *cub) {

}