#include "../includes/minirt.h"

int	arg_validate(int argc);

int	main(int argc, char **argv)
{
	t_app	app;

	if (!arg_validate(argc))
		return (1);
	app_init(&app);
	init_camera(&app.camera);
	if (!scene_load(argv[1], &app))
		return (1);
	if (!init_mxl(&app))
		return (1);
	if (!init_image(&app))
		return (1);
	render_scene(&app);
	render_image(&app);
	init_hooks(&app);
	mlx_loop(app.mlx);
	return (0);
}

int	arg_validate(int argc)
{
	if (argc != 2)
	{
		printf("Error\nA scene file argument is required\n");
		return (0);
	}
	else
		return (1);
}