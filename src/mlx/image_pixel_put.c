#include "../../includes/minirt.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr
	+ (y * img->line_len)
	+ (x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	render_image(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
}