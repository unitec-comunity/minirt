#include "../includes/minirt.h"

int	arg_validate(int argc);

int	main(int argc, char **argv)
{
	t_app	app;

	if (!arg_validate(argc))
		return (1);
	if (!scene_validate(argv[1]))
		return (1);
	app_init(&app);
	init_camera(&app.camera);

	app.light.position = vec3(2, 2, 0);
	app.light.brightness = 1.0;
	app.ambient.ratio = 0.2;
	app.object_count = 0;

	app.objects[0].type = OBJ_PLANE;
	app.objects[0].position = vec3(0, -1, 5);
	app.objects[0].normal = vec3(0, 1, 0);
	app.objects[0].color.r = 120;
	app.objects[0].color.g = 120;
	app.objects[0].color.b = 120;

	app.objects[1].type = OBJ_CYLINDER;
	app.objects[1].position = vec3(0, 0, 5);
	app.objects[1].normal = vec3(1, 1, 1);
	app.objects[1].color.r = 255;
	app.objects[1].color.g = 255;
	app.objects[1].color.b = 0;
	app.objects[1].radius = 1.0;
	app.objects[1].height = 2.0;

	app.object_count = 2;

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
