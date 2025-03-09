
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

int	valid_move(int key, t_cub *cub)
{
	t_mgam2i	pos;

	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player / 2),
		cub->cam->player_pos.y + (ratio_player / 2)};

	if (key == XK_w)
		if (pos.y - SPACE < 0)
			return (0);
	if (key == XK_s)
		if (pos.y + SPACE > cub->data->height)
			return (0);			
	if (key == XK_a)
		if (pos.x - SPACE < 0)
			return (0);
	if (key == XK_d)
		if (pos.x + SPACE > cub->data->width)
			return (0);
	return (1);
}	


int	keyPressed(int key, t_cub *cub)
{
	t_mgam2i	pos;
	pos = (t_mgam2i){cub->cam->player_pos.x + (ratio_player) - cub->map->l / 4,
			cub->cam->player_pos.y + (ratio_player) - cub->map->L / 2};
	
	if (key == XK_w && valid_move(key, cub)) {
		cub->cam->player_pos -= (t_mgam2f){0, SPACE};
		cub->cam->look -= (t_mgam2f){0, SPACE};
	}
	if (key == XK_s && valid_move(key, cub)) {
		cub->cam->player_pos += (t_mgam2f){0, SPACE};
		cub->cam->look += (t_mgam2f){0, SPACE};
	}
	if (key == XK_a && valid_move(key, cub)) {
		cub->cam->player_pos -= (t_mgam2f){SPACE, 0};
		cub->cam->look -= (t_mgam2f){SPACE, 0};
	}
	if (key == XK_d && valid_move(key, cub)) {
		cub->cam->player_pos += (t_mgam2f){SPACE, 0};
		cub->cam->look += (t_mgam2f){SPACE, 0};
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
