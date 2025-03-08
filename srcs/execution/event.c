
#include "../../includes/cub3d.h"

/// faire les rayons 10 cases par 10 cases jusqu'a ce que ca hit un mur


void	lookMove(t_mgam2f *look)
{
	(void)look;
	
}

int	keyPressed(int key, t_cub *cub)
{
	if (key == XK_w) {
		// mlx_hook(cub->data->win, XK_w, (1L<<0), &press_w, cub);
		// mlx_hook(cub->data->win, XK_w, (1L<<1), &release_w, cub);
		cub->cam->player_pos -= (t_mgam2f){0, 10.1};
		cub->cam->look -= (t_mgam2f){0, 10.1};
	}
	if (key == XK_s) {
		// mlx_hook(cub->data->win, XK_s, (1L<<0), &press_s, cub);
		// mlx_hook(cub->data->win, XK_s, (1L<<1), &release_s, cub);
		cub->cam->player_pos += (t_mgam2f){0, 10.1};
		cub->cam->look += (t_mgam2f){0, 10.1};
	}
	if (key == XK_a) {
		// mlx_hook(cub->data->win, XK_a, (1L<<0), &press_a, cub);
		// mlx_hook(cub->data->win, XK_a, (1L<<1), &release_a, cub);
		cub->cam->player_pos -= (t_mgam2f){10.1, 0};
		cub->cam->look -= (t_mgam2f){10.1, 0};
	}
	if (key == XK_d) {
		// mlx_hook(cub->data->win, XK_d, (1L<<0), &press_d, cub);
		// mlx_hook(cub->data->win, XK_d, (1L<<1), &release_d, cub);
		cub->cam->player_pos += (t_mgam2f){10.1, 0};
		cub->cam->look += (t_mgam2f){10.1, 0};
	}
	if (key == XK_Left) {
		// mlx_hook(cub->data->win, XK_Left, (1L<<0), &press_left, cub);
		// mlx_hook(cub->data->win, XK_Left, (1L<<1), &release_left, cub);
		cub->cam->look += (t_mgam2f){0, 10.00159};
		lookMove(&cub->cam->look);
	}
	if (key == XK_Right) {
		// mlx_hook(cub->data->win, XK_Right, (1L<<0), &press_right, cub);
		// mlx_hook(cub->data->win, XK_Right, (1L<<1), &release_right, cub);
		cub->cam->look -= (t_mgam2f){0, 10.00159};
		lookMove(&cub->cam->look);
	}
	if (key == XK_Escape)
		end_win(cub);

	raycast(cub);
	return (0);
}

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