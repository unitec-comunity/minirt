#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1280
# define HEIGHT 720
#define MAX_OBJECTS 100

# include "../depemdences/minilibx-linux/mlx.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	double	fov;
}	t_camera;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_color	color;
}	t_light;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_object_type;

typedef struct s_object
{
	t_object_type	type;
	t_color			color;
	t_vec3			position;
	t_vec3			normal;
	double			radius;
	double			height;
}	t_object;

typedef struct s_hit
{
	double		t;
	t_object	*object;
}	t_hit;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_camera	camera;
	t_ambient	ambient;
	t_light	light;
	t_object		objects[MAX_OBJECTS];
	int				object_count;
}	t_app;

void	app_init(t_app *app);
void	init_hooks(t_app *app);
int		scene_load(const char *path, t_app *app);
int		scene_parse_line(char *line, int line_no, int *state, t_app *app);
int		scene_parse_record(char **tokens, int count, int *state, t_app *app);
int		scene_parse_object(char **tokens, int count, int *state, t_app *app);
int		parse_number(const char *str, double *value);
int		parse_vector(char *str, int mode, t_vec3 *result);
int		parse_scalar_range(char *str, double min, double max, int exclusive);
int		scene_string_equal(const char *left, const char *right);
int		scene_color(char *str, t_color *color);
int		apply_lighting(t_color object, t_app *app, double diffuse,
			t_color *result);

int		init_mxl(t_app *app);
int		key_press(int keycode, t_app *app);
int		init_image(t_app *app);
void	img_pixel_put(t_img *img, int x, int y, int color);
void	render_scene(t_app *app);
void	render_image(t_app *app);
int		create_color(int r, int g, int b);

t_vec3	vec3(double x, double y, double z);
t_vec3	vect_add(t_vec3 a, t_vec3 b);
t_vec3	vect_sub(t_vec3 a, t_vec3 b);
t_vec3	vect_scale(t_vec3 vector, double number);

double	vect_dot(t_vec3 a, t_vec3 b);
double	vec3_length(t_vec3 v);
t_vec3	vect_normalize(t_vec3 v);
t_ray	ray_create(t_vec3 origin, t_vec3 direction);
void	init_camera(t_camera *camera);
t_vec3	vect_cross(t_vec3 a, t_vec3 b);
t_ray	camera_ray(t_camera *camera, int x, int y);
double	intersect_sphere(t_ray ray, t_object *object);
t_vec3	ray_at(t_ray ray, double t);
t_vec3	object_normal(t_object *object, t_vec3 point);
t_vec3	sphere_normal(t_object *object, t_vec3 point);
double	diffuse_light(t_vec3 normal, t_vec3 light_dir);
int	color_from_intensity(double intensity);
double	final_intensity(double ambient, double diffuse);
t_color	color_scale(t_color color, double intensity);
int	color_to_int(t_color color);
int	is_in_shadow(t_app *app, t_vec3 hit_point, t_vec3 normal);
t_hit	find_closest_hit(t_app *app, t_ray ray);
double	intersect_object(t_ray ray, t_object *object);
double	intersect_plane(t_ray ray, t_object *object);
int	cylinder_height_valid(t_ray ray, t_object *object, double t);
double	intersect_cylinder(t_ray ray, t_object *object);
t_vec3	cylinder_normal(t_object *object, t_vec3 point);
double	intersect_cylinder_caps(t_ray ray, t_object *object);
t_vec3	vect_cross(t_vec3 a, t_vec3 b);
#endif
