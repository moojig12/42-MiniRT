#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

// Constants
# define PI 3.14159265358979323846

// Max depth of bounces for tracing
# define MAXDEPTH 5

// objects
# define AMBIENCE 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

// linear congruential generator constants
# define A 1664525
# define C 1013904223
# define M 0xFFFFFFFF

typedef struct s_obj t_obj;

typedef enum e_object_type {
	OBJECT_SPHERE,
	OBJECT_PLANE,
	OBJECT_CYLINDER
}	t_object_type;

/* typedef struct s_object {
	t_object_type	type;
	void			*data;
}	t_obj; */

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_ray {
	t_vec	origin;
	t_vec	dest;
}	t_ray;
typedef struct s_camera {
	t_vec	pos;
	t_vec	norm;
	int		width;
	int		height;
	int		fov;
}	t_camera;

typedef struct s_material {
	t_rgb	reflectance;
	t_rgb	emission;
	t_rgb	color;
}	t_mat;

typedef struct s_ambient {
	double	ratio;
	t_rgb	color;
}	t_ambient;

typedef struct s_light {
	t_vec	pos;
	double	brightness;
	t_rgb	color;
}	t_light;

typedef struct s_sphere {
	t_vec	pos;
	double	diameter;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane {
	t_vec	pos;
	t_vec	norm;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder {
	t_vec	pos;
	t_vec	norm;
	double	diameter;
	double	height;
	t_rgb	color;
}	t_cyl;

typedef struct s_obj {
	int	type;
	void	*data;
	t_obj	*next;
}	t_obj;

typedef struct s_intersection {
	t_vec	origin;
	t_vec	norm;
	t_vec	point;
	t_rgb	emittance;
	double	distance;
	int		hit;
}	t_intersection;

typedef struct s_screen {
	double	width;
	double	height;
	double	aspect_ratio;
	t_vec	up;
	t_vec	right;
}	t_screen;

typedef struct s_world {
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*light;
	t_sphere	*sphere;
	t_cyl		*cyl;
	t_plane		*plane;
	t_obj		*obj;
	int			object_num;
}	t_world;

typedef struct s_main {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_world	*world;
}	t_main;

/* typedef struct s_ray
{

}	t_ray; */

// Main pipeline

int	main_pipeline(t_main *main);

// Render

t_intersection	find_path(t_ray ray, t_world *world);

// Parsing

void	parse_world(t_main *main, char **argv);
int		parse_amb(t_main *main, char *input, int index);
int		parse_light(t_main *main, char *input, int index);
int		parse_cam(t_main *main, char *input, int index);
int		parse_cyl(t_cyl *cyl, char *input, int index);
int		parse_plane(t_plane *plane, char *input, int index);
int		parse_sphere(t_sphere *sphere, char *input, int index);

// Parsing utilities

int		pop_color(t_rgb *rgb, char **input);
int		pop_vec(t_vec *vec, char **input, double *range);

// Utilities

int		*alloc_int(int a, int b);
double	*alloc_float(double a, double b);
int		ft_range(int num, int min, int max);
int		ft_range_f(double num, double min, double max);
double	ft_atof(char *str);
int		close_window(t_main	*main);

// Vector operations
t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scalar(t_vec a, double b);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_normalize(t_vec v);

// Color operations
int		pack_color(int r, int g, int b);
t_rgb	color_add(t_rgb a, t_rgb b);
t_rgb	color_scalar(t_rgb color, double scalar);
t_rgb	color_multiply(t_rgb a, t_rgb b);
double	vec_dot(t_vec a, t_vec b);
t_rgb	ret_color(int r, int g, int b);

// Randomness

unsigned int	ft_rand(void);
double			random_double(void);
double			random_double_range(double min, double max);
t_vec			random_vec(void);
t_vec			random_vec_range(double min, double max);

#endif