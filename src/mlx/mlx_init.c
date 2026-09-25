#include "../../includes/minirt.h"

int	init_mxl(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		printf("Erro ao carregar mini_lbx");
		return (0);
	}
	app->win = mlx_new_window(app->mlx, WIDTH, HEIGHT, "miniRT");
	if (!app->win)
		return (0);
	return (1);
}