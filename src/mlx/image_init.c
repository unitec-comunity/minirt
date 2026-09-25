#include "../../includes/minirt.h"

int	init_image(t_app *app)
{
	app->img.img = mlx_new_image(app->mlx, WIDTH, HEIGHT);
	if (!app->img.img)
	{
		printf("Erro ao carregar imagem minilix");
		return (0);
	}
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bpp,
		&app->img.line_len, &app->img.endian);
	return (1);
}