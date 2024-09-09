#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define AMBIENCE 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6
typedef enum e_object_type {
	OBJECT_SPHERE,
	OBJECT_PLANE,
	OBJECT_CYLINDER
}	t_object_type;

typedef struct s_object {
	t_object_type	type;
	void			*data;
}	t_obj;

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
	int		fov;
}	t_camera;

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

typedef struct s_world {
	t_ambient	*amb;
	t_camera	*cam;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cyl		*cyl;
}	t_world;

typedef struct s_main {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_world	world;
}	t_main;

/* typedef struct s_ray
{

}	t_ray; */

void	parse_world(t_main *main, char **argv);

#endif