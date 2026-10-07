#include "../includes/minirt.h"

int	arg_validate(int argc);

int	main(int argc, char **argv)
{
	t_app	app;

	(void)argv;
	if (!arg_validate(argc))
		return (1);
	app_init(&app);
	init_camera(&app.camera);

	app.light.position = vec3(2, 4, 1);
	app.light.brightness = 1.0;
	app.ambient.ratio = 0.2;
	app.object_count = 0;

	app.objects[0].type = OBJ_PLANE;
	app.objects[0].position = vec3(0, -1, 6);
	app.objects[0].normal = vec3(0, 1, 0);
	app.objects[0].color.r = 120;
	app.objects[0].color.g = 120;
	app.objects[0].color.b = 120;

	app.objects[1].type = OBJ_CYLINDER;
	app.objects[1].position = vec3(-1, 1, 6);
	app.objects[1].normal = vec3(0, 1, 0);
	app.objects[1].color.r = 255;
	app.objects[1].color.g = 255;
	app.objects[1].color.b = 0;
	app.objects[1].radius = 1.0;
	app.objects[1].height = 2.0;

	app.objects[2].type = OBJ_SPHERE;
	app.objects[2].position = vec3(-2.5, 0, 6);
	app.objects[2].color.r = 255;
	app.objects[2].color.g = 0;
	app.objects[2].color.b = 0;
	app.objects[2].radius = 1.0;

	app.objects[3].type = OBJ_SPHERE;
	app.objects[3].position = vec3(2.5, 0, 6);
	app.objects[3].color.r = 0;
	app.objects[3].color.g = 0;
	app.objects[3].color.b = 255;
	app.objects[3].radius = 1.0;

	app.object_count = 4;

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
		printf("Obrigatorio o envio do ficheiro!");
		return (0);
	}
	else
		return (1);
}
