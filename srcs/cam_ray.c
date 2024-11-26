#include "../minirt.h"

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;

	aspect_ratio = ((double)cam->width / (double)cam->height);
	
	// Normalized Device Coordinates
	double	ndc_x = (x + 0.5 ) / cam->width;
	double	ndc_y = (y + 0.5 ) / cam->height;

	pixel_x = (2 * ndc_x - 1) * tan((double)cam->fov * 0.5 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ndc_y) * tan((double)cam->fov * 0.5 * PI / 180);

	// Create the camera basis: right, up, and forward
	t_vec forward = vec_normalize(cam->direction);
	t_vec right = vec_normalize(vec_cross(cam->norm, forward));
	t_vec up = vec_cross(forward, right);

	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(right, pixel_x), vec_scalar(up, pixel_y)), vec_scalar(forward, 1));
	ray.dest = vec_normalize(ray.dest);

	return (ray);
}

t_ray	gen_ray_low(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;

	aspect_ratio = ((double)cam->width / (double)cam->height);
	
	// Normalized Device Coordinates
	double	ndc_x = (x + 0.5 ) / cam->width;
	double	ndc_y = (y + 0.5 ) / cam->height;

	pixel_x = (2 * ndc_x - 1) * tan((double)cam->fov * 0.5 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ndc_y) * tan((double)cam->fov * 0.5 * PI / 180);

	// Create the camera basis: right, up, and forward
	t_vec forward = vec_normalize(cam->direction);
	t_vec right = vec_normalize(vec_cross(cam->norm, forward));
	t_vec up = vec_cross(forward, right);

	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(right, pixel_x), vec_scalar(up, pixel_y)), vec_scalar(forward, 1));
	ray.dest = vec_normalize(ray.dest);

	return (ray);
}
