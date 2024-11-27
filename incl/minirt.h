#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include <time.h>
# include <pthread.h>
# include <X11/Xlib.h>

// Constants
# define PI 3.14159265358979323846
# define EPSILON 0.0001
# define STATIC_SAMPLE 4

// Max depth of bounces for tracing
# define MAXDEPTH 8

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
typedef struct s_main t_main;

typedef enum e_fidelity {
	LOW,
	HIGH
}	t_fidelity;

typedef enum e_rotation_index {
	X_AXIS,
	Y_AXIS,
	Z_AXIS
}	t_rotation_index;

typedef enum e_objection_selection {
	OBJ_CAM = 49,
	OBJ_LIGHT = 50,
	OBJ_SPHERE = 51,
	OBJ_CYL = 52,
	OBJ_PLANE = 53,
}	t_objection_selection;

typedef enum e_movement_keys {
	FORWARD = 119,
	LEFT = 97,
	BACK = 115,
	RIGHT = 100,
	UP = 32,
	DOWN = 65507,
	ROTATE_LEFT = 113,
	ROTATE_RIGHT = 101,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_U = 117,
	KEY_O = 111,
	KEY_P = 112,
	KEY_R = 114
}	t_movement_keys;

typedef enum e_escape_key {
	ESC_WIN = 65307
}	t_escape_key;

typedef enum e_object_type {
	OBJECT_SPHERE,
	OBJECT_PLANE,
	OBJECT_CYLINDER
}	t_object_type;

typedef struct s_vector {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vec;

typedef struct s_matrix {
	double matrix[4][4];
}	t_matrix;

typedef struct s_rgb {
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef struct s_ray {
	t_vec	origin;
	t_vec	dest;
	// t_vec	norm;
}	t_ray;
typedef struct s_camera {
	t_vec	pos;
	t_vec	norm;
	t_vec	direction;
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
	struct s_light	*next;
}	t_light;

typedef struct s_sphere {
	t_vec	pos;
	double	diameter;
	t_rgb	color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane {
	t_vec	pos;
	t_vec	norm;
	t_rgb	color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder {
	t_vec	pos;
	t_vec	norm;
	double	direction;
	double	diameter;
	double	height;
	t_rgb	color;
	struct s_cylinder	*next;
}	t_cyl;

typedef struct s_obj {
	int		type;
	void	*data;
	t_obj	*next;
}	t_obj;

typedef struct s_intersection {
	t_vec	origin;
	t_vec	norm;
	t_vec	point;
	t_rgb	color;
	double	reflectance;
	double	diffuse;
	double	specular;
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

typedef struct s_selected {
	int		type;
	t_vec	*pos;
	t_vec	*norm;
	t_vec	*dir;
}	t_selected;

typedef struct s_world {
	t_ambient	*amb;
	t_camera	*cam;
	t_light		*light;
	t_sphere	*sphere;
	t_cyl		*cyl;
	t_plane		*plane;
	t_obj		*objlist;
	t_obj		**selected;
	int			object_num;
}	t_world;

typedef struct s_render {
	pthread_t	thread;
	void		*mlx;
	void		*win;
	void		*image_ptr;
	int			*render_switch;
	t_world		*world;
	t_main		*main;
	pthread_t	*next;
	pthread_mutex_t	**render_lock;
	pthread_mutex_t	*object_lock;
	pthread_mutex_t	*write_lock;
}	t_render;

typedef struct s_move_thread {
	pthread_t	thread;
	void		*mlx;
}	t_move_thread;

typedef struct s_main {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		render_switch;
	t_rgb	**output;
	t_world	*world;
	t_render	thread[4];
	pthread_mutex_t	**output_pixel;
	pthread_mutex_t	write_lock;
}	t_main;

/* typedef struct s_ray
{

}	t_ray; */

// Main pipeline

int				main_pipeline(t_main *main);

// Render
void			*render(void *arg);
t_rgb			trace(t_ray ray, int depth, t_world *world);
t_ray			gen_ray(t_camera *cam, int x, int y);
t_ray			gen_ray_low(t_camera *cam, int x, int y);
int				is_occluded(t_ray shadow_ray, t_world *world, double light_distance);
t_intersection	find_path(t_ray ray, t_world *world);
void			flush_screen(t_main *main, t_rgb **output);

// Movement

int				movement(int key_code, t_main *main);
int				move(t_obj *obj, t_vec	movement, int movement_code);
int				rotate_object(t_obj *object, t_vec rotation);
t_vec			rotate_angle(int direction, double angle);
void			check_selection(int key_code, t_main *main);
t_vec			movement_rotation(t_vec movement, int movement_code);
void			set_selection(t_obj **base_selection, t_main *main, int target);
int				rotation_selected(int key_code, t_obj *selected);
int				movement_selected(int key_code, t_obj *selected);
t_vec			move_angle(int direction, double angle);

// Parsing

t_world			*parse_world(t_world *world, char **argv);
void			init_world(t_world *world);

// Parsing obj

t_obj	*ft_add_obj_lst(int type, t_world *world, t_obj **objlist);
t_obj	*ft_lstlast_mrt(t_obj *lst);
void	ft_lstadd_back_mrt(t_obj **lst, t_obj *new);
t_obj	*add_light(t_light *lightlist);
t_obj	*add_sobj(int type, void *list);

// Parsing utilities

int		pop_color(t_rgb *rgb, char **input);
int		pop_vec(t_vec *vec, char **input, double *range, double type);
int		pop_fov(int *fov, char *input, int *range);
int		ft_strcmp(const char *s1, const char *s2);
int		check_file(char *file);
int		check_size_matrix(char **matrix);

// Parsing amb

t_ambient	*parse_amb(t_world *world, char **input);

// Parsing cam

t_camera	*parse_cam(t_world *world, char **input);

// Parsing light

t_light	*ft_lstlast_lig_mrt(t_light *lst);
void	ft_lstadd_back_lig_mrt(t_light **lst, t_light *new);
int		parse_light(t_world *world, char **input);
void	print_light(t_light *ptr);

//Parsing cyl

int		parse_cyl(t_world *world, char **input);
t_cyl	*ft_lstlast_cyl_mrt(t_cyl *lst);
void	ft_lstadd_back_cyl_mrt(t_cyl **lst, t_cyl *new);

//Parsing sphere

int			parse_sphere(t_world *world, char **input);
t_sphere	*ft_lstlast_sphere_mrt(t_sphere *lst);
void		ft_lstadd_back_sphere_mrt(t_sphere **lst, t_sphere *new);

// Parsing plane

int		parse_plane(t_world *world, char **input);
t_plane	*ft_lstlast_plane_mrt(t_plane *lst);
void	ft_lstadd_back_plane_mrt(t_plane **lst, t_plane *new);

// error
void	exit_err(char *message, int code, t_main *main);
void	exit_err_init(char *msg, int code, t_world *world);
void	free_world(t_world *world);
void	free_main(t_main *main);
void	free_tab(char **tab);

// Checks

int		check_size_matrix(char **matrix);
int		check_file(char *file);

// Utilities

int		*alloc_int(int a, int b);
double	*alloc_float(double a, double b);
int		ft_range(int num, int min, int max);
int		ft_range_f(double num, double min, double max);
double	ft_atof(char *str);
int		print_vec(char *string,t_vec vec);
int		close_window(t_main	*main);
int		print_color(char *string, t_rgb color);
int		print_matrix(char *string, t_matrix mat);
t_selected	discern_object(t_obj *obj);
double	trace_time(int type);
void	print_position(t_obj *selection);

// Vector operations

t_vec	vec(double x, double y, double z, double w);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scalar(t_vec a, double b);
t_vec	vec_cross(t_vec a, t_vec b);
t_vec	vec_multiply(t_vec a, t_vec b);
t_vec	vec_normalize(t_vec v);
t_vec	vec_orthogonal(t_vec vec);
double	vec_length(t_vec v);

// Color operations

int		pack_color(t_rgb color);
t_rgb	color_add(t_rgb a, t_rgb b);
t_rgb	color_sub(t_rgb a, t_rgb b);
t_rgb	color_scalar(t_rgb color, double scalar);
t_rgb	color_scalar_div(t_rgb a, double scalar);
t_rgb	color_multiply(t_rgb a, t_rgb b);
double	vec_dot(t_vec a, t_vec b);
t_rgb	ret_color(double r, double g, double b);
t_rgb	color_normalize(t_rgb color);

// Matrix operations

t_vec	matrix_translation(t_vec data, t_vec translate);
t_vec	matrix_rotation(t_vec data, t_vec rotate);

// Randomness

unsigned int	ft_rand(void);
double			random_double(void);
double			random_double_range(double min, double max);
t_vec			random_vec(double w);
t_vec			random_vec_range(double min, double max, double w);

#endif