#include "../../includes/raycasting.h"

double	lengthRay(t_cub *cub, t_mgam2f startP, t_mgam2f endP)
{
	int	a;
	int	b;

	a = endP.x - startP.x;
	b = endp.y - endP.y;
	return (sqrt((a * a) + (b * b)));
}