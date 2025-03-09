
#include "../../includes/cub3d.h"

/// faire les rayons 10 cases par 10 cases jusqu'a ce que ca hit un mur


void	lookMove(t_cam *cam, int key)
{
	printf("Left or right pressed\n");
	printf("Before : {%f, %f}\n", cam->look[0], cam->look[1]);
	if (key == XK_Left)
	{
		if (cam->look[0] < 0 && cam->look[1] > 0)
			cam->look += (t_mgam2f){-10, -10};
		else if (cam->look[0] > 0 && cam->look[1] < 0)
			cam->look += (t_mgam2f){+10, +10};
		else if (cam->look[0] < 0 && cam->look[1])
			cam->look += (t_mgam2f){-10, +10};
		else if (cam->look[0] > 0 && cam->look[1])
			cam->look += (t_mgam2f){+10, -10};
	}
	else
	{
		if (cam->look[0] < 0 && cam->look[1] > 0)
			cam->look += (t_mgam2f){+10, +10};
		else if (cam->look[0] > 0 && cam->look[1] < 0)
			cam->look += (t_mgam2f){-10, -10};
		else if (cam->look[0] < 0 && cam->look[1] < 0)
			cam->look += (t_mgam2f){+10, -10};
		else if (cam->look[0] > 0 && cam->look[1] > 0)
			cam->look += (t_mgam2f){-10, +10};
	}
	printf("After : {%f, %f}\n", cam->look[0], cam->look[1]);
}

int	keyPressed(int key, t_cub *cub)
{
	if (key == XK_w) {
		cub->cam->player_pos -= (t_mgam2f){0, 10};
		cub->cam->look -= (t_mgam2f){0, 10};
	}
	if (key == XK_s) {
		cub->cam->player_pos += (t_mgam2f){0, 10};
		cub->cam->look += (t_mgam2f){0, 10};
	}
	if (key == XK_a) {
		cub->cam->player_pos -= (t_mgam2f){10, 0};
		cub->cam->look -= (t_mgam2f){10, 0};
	}
	if (key == XK_d) {
		cub->cam->player_pos += (t_mgam2f){10, 0};
		cub->cam->look += (t_mgam2f){10, 0};
	}
	if (key == XK_Left || key == XK_Right) {
		if (key == XK_Left)
			lookMove(cub->cam, XK_Left);
		else
			lookMove(cub->cam, XK_Right);
	}
	if (key == XK_Escape)
		end_win(cub);
	raycast(cub);
	return (0);
}
