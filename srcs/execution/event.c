
#include "../../includes/cub3d.h"

/// faire les rayons 10 cases par 10 cases jusqu'a ce que ca hit un mur


void	lookMove(t_cam *cam, int key)
{
	if (key == XK_Left)
	{
		if (cam->look[0] < 0 && cam->look[1] > 0) {
			cam->look[0] -= 22;
			cam->look[1] -= 22;
		}
		else if (cam->look[0] > 0 && cam->look[1] < 0) {
			cam->look[0] += 22;
			cam->look[1] += 22;
		}
		else if (cam->look[0] < 0 && cam->look[1] < 0) {
			cam->look[0] -= 22;
			cam->look[1] += 22;
		}
		else if (cam->look[0] > 0 && cam->look[1] > 0) {
			cam->look[0] += 22;
			cam->look[1] -= 22;
		}
	}
	else
	{
		if (cam->look[0] < 0 && cam->look[1] > 0) {
			cam->look[0] += 22;
			cam->look[1] += 22;
		}
		else if (cam->look[0] > 0 && cam->look[1] < 0) {
			cam->look[0] -= 22;
			cam->look[1] -= 22;
		}
		else if (cam->look[0] < 0 && cam->look[1] < 0) {
			cam->look[0] += 22;
			cam->look[1] -= 22;
		}
		else if (cam->look[0] > 0 && cam->look[1] > 0) {
			cam->look[0] -= 22;
			cam->look[1] += 22;
		}
	}
}

int	keyPressed(int key, t_cub *cub)
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

/*
int	press_w(t_cub *cub) {
	cub->cam->player_pos -= (t_mgam2f){0, 0.1};
	cub->cam->look -= (t_mgam2f){0, 0.1};
	return (0);
}

int	release_w(t_cub *cub) {
	(void)cub;
	return (0);
}

int	press_a(t_cub *cub) {
	cub->cam->player_pos -= (t_mgam2f){0.1, 0};
	cub->cam->look -= (t_mgam2f){0.1, 0};
	return (0);
}

int	release_a(t_cub *cub) {
	(void)cub;
	return (0);
}

int	press_s(t_cub *cub) {
	cub->cam->player_pos += (t_mgam2f){0, 0.1};
	cub->cam->look += (t_mgam2f){0, 0.1};
	return (0);
}

int	release_s(t_cub *cub) {
	(void)cub;
	return (0);
}

int	press_d(t_cub *cub) {
	cub->cam->player_pos += (t_mgam2f){0.1, 0};
	cub->cam->look += (t_mgam2f){0.1, 0};
	return (0);
}

int	release_d(t_cub *cub) {
	(void)cub;
	return (0);
}

int	press_left(t_cub *cub) {
	cub->cam->look += (t_mgam2f){0, 10.00159};
	lookMove(&cub->cam->look);
	return (0);
}

int	release_left(t_cub *cub) {
	(void)cub;
	return (0);
}

int	press_right(t_cub *cub) {
	cub->cam->look -= (t_mgam2f){0, 10.00159};
	lookMove(&cub->cam->look);
	return (0);
}

int	release_right(t_cub *cub) {
	(void)cub;
	return (0);
}


void	press(int key, t_cub *cub) {
	if (key == XK_w) {
		cub->cam->player_pos -= (t_mgam2f){0, 0.1};
		cub->cam->look -= (t_mgam2f){0, 0.1};
	}
	if (key == XK_s) {
		cub->cam->player_pos += (t_mgam2f){0, 0.1};
		cub->cam->look += (t_mgam2f){0, 0.1};
	}
	if (key == XK_a) {
		cub->cam->player_pos -= (t_mgam2f){0.1, 0};
		cub->cam->look -= (t_mgam2f){0.1, 0};
	}
	if (key == XK_d) {
		cub->cam->player_pos += (t_mgam2f){0.1, 0};
		cub->cam->look += (t_mgam2f){0.1, 0};
	}
	if (key == XK_Left || key == XK_Right) {
		// cub->cam->look += (t_mgam2f){0, 0.00159};
		cub->cam->look += (t_mgam2f){0, 10.00159};
		lookMove(&cub->cam->look);
	}
	if (key == XK_Escape)
		end_win(cub);
	raycast(cub);
}

void	release(int key, t_cub *cub) {
	if (key == XK_w) {
		cub->cam->player_pos -= (t_mgam2f){0, 0};
		cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_s) {
		cub->cam->player_pos += (t_mgam2f){0, 0};
		cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_a) {
		cub->cam->player_pos -= (t_mgam2f){0, 0};
		cub->cam->look -= (t_mgam2f){0, 0};
	}
	if (key == XK_d) {
		cub->cam->player_pos += (t_mgam2f){0, 0};
		cub->cam->look += (t_mgam2f){0, 0};
	}
	if (key == XK_Left || key == XK_Right) {
		// cub->cam->look += (t_mgam2f){0, 0.00159};
		cub->cam->look += (t_mgam2f){0, 0};
		lookMove(&cub->cam->look);
	}
	if (key == XK_Escape)
		end_win(cub);
}
*/