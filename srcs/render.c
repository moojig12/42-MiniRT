#include "minirt.h"

void	key_handles(t_main *main)
{
	mlx_key_hook(main->win, movement, main);
	mlx_hook(main->win, 17, 1L<<17, close_window, main);
}

t_vec	cone_pewpew(t_vec norm)
{
	t_vec dir;

	dir = random_vec(0);

	if (vec_dot(dir, norm) < 0)
		dir = vec_scalar(dir, -1);

	return vec_normalize(dir);
}

t_ray	gen_ray(t_camera *cam, int x, int y)
{
	t_ray ray;
	double	aspect_ratio;
	double	pixel_x;
	double	pixel_y;
	double	jitter_x = random_double_range(-0.0, 0.0);
	double	jitter_y = random_double_range(-0.0, 0.0);

	aspect_ratio = cam->width / cam->height;
	
	pixel_x = (2 *((x + 0.5 + jitter_x) / cam->width) - 1) * tan(cam->fov / 2 * PI / 180) * aspect_ratio;
	pixel_y = (1 - 2 * ((y + 0.5 + jitter_y) / cam->height)) * tan(cam->fov / 2 * PI / 180);

	// Create the camera basis: right, up, and forward
	t_vec forward = vec_normalize(cam->direction);
	t_vec right = vec_normalize(vec_cross(cam->norm, forward));
	t_vec up = vec_cross(forward, right);

	ray.origin = cam->pos;
	ray.dest = vec_add(vec_add(vec_scalar(right, pixel_x), vec_scalar(up, pixel_y)), vec_scalar(forward, 1));
	ray.dest = vec_normalize(ray.dest);

	return (ray);
}

	// BRDF calculation for materials, not sure if it works 100% yet
/* double	brdf_calculation(t_intersection intersection, t_ray ray, t_vec norm)
{
	double	fresnel;
	double	diffuse;
	double	specular;
	double	dot_product = vec_dot(ray.dest, norm);

	 // Fresnel reflectance (e.g., Schlick's approximation)
	fresnel = intersection.reflectance + (1 - intersection.reflectance) * pow(1 - dot_product, 5);

	// Diffuse component
	diffuse = intersection.diffuse * fmax(0.0, dot_product);

	// Specular component (e.g., Cook-Torrance model)
	specular = fresnel * intersection.specular;

	return (diffuse + specular);
} */

bool	in_shadow(t_world *world, t_intersection intersection)
{
	t_vec	shadow_origin;
	t_vec	shadow_direction;
	double	light_dis;
	t_ray	shadow_ray;
	t_intersection	new_intersection;

	shadow_origin = vec_add(intersection.point, vec_scalar(intersection.norm, EPSILON));
	shadow_direction = vec_normalize(vec_sub(world->light->pos, shadow_origin));
	light_dis = vec_length(vec_sub(world->light->pos, shadow_origin));
	shadow_ray = new_ray(shadow_origin, shadow_direction);
	new_intersection = find_path(shadow_ray, world);
	if(new_intersection.hit && new_intersection.distance > 0 && new_intersection.distance < light_dis)
		return(true);
	else
		return (false);

}
t_rgb	lighting(t_intersection intersection,t_world *world, t_ray ray)
{
	t_rgb	effective_color;
	t_rgb	ambient;
	t_vec	light_vec;
	double	light_dot_normal;
	t_rgb	diffuse;
	t_rgb	specular;
	t_vec	reflect_vec;
	double reflect_dot_eye;
	t_vec	eye;
	double	factor;

	effective_color = color_multiply(intersection.color, world->amb->color);
	ambient = color_scalar(effective_color, world->amb->ratio);
	if(in_shadow)
		return(ambient);
	light_vec = vec_normalize(vec_sub(world->light->pos, intersection.point));
	light_dot_normal = vec_dot(light_vec, intersection.norm);
	diffuse = ret_color(0, 0, 0);
	specular = ret_color(0, 0, 0);
	eye = vec_neg(ray.dest);
	if(light_dot_normal > 0)
	{
		diffuse = color_scalar(effective_color, (intersection.diffuse * light_dot_normal));
		reflect_vec = reflect(vec_neg(light_vec), intersection.norm);
		reflect_dot_eye = vec_dot(reflect_vec, eye);
		if (reflect_dot_eye > 0)
		{
			factor = pow(reflect_dot_eye, intersection.reflectance);
			specular = color_scalar(world->amb->color, (intersection.specular * factor));
		}
		return(color_add(color_add(diffuse, specular), ambient));
	}

}

	// The function for simulating and bouncing a ray off an object
t_rgb	trace_path(t_world *world, t_ray ray, int depth)
{
	t_intersection	intersection;
	t_rgb	return_color;
	t_rgb	incoming;
	t_ray	new_ray;

	return_color = world->amb->color;
	while(depth <= MAXDEPTH){
		intersection = find_path(ray, world);
		if (intersection.hit)
			return(return_color = lighting(intersection, world, ray));
		depth++;
	}
		return (return_color);

		// Iterate over each object in the world and find the closest intersection.
			// Also fetches data relating to the object such as Material and Norm direction
	//	return	(return_color);
	//else
		// initialize a new ray from the POINT of Intersection and random direction
	//new_ray.origin = intersection.point;
	// new_ray.dest = vec_sub(ray.dest, vec_scalar(intersection.norm, 2 * vec_dot(ray.dest, intersection.norm)));
		// Shoots random rays in possible direction
	//new_ray.dest = cone_pewpew(intersection.norm);

		// Calculations i found off the internet for BRDF
	//double	cos_theta = vec_dot(new_ray.dest, intersection.norm);
	//double	BRDF = brdf_calculation(intersection, new_ray, intersection.norm);

		// Shoot the next ray recursively
	//incoming = trace_path(world, new_ray, depth + 1);

	//return_color = lighting(intersection, world);
/* 		// Ambience
	return_color = color_add(incoming, color_scalar(world->amb->color, world->amb->ratio));

		// Calculate light position and shadow
		t_ray shadow_ray;

		shadow_ray.origin = intersection.point;
		shadow_ray.dest = vec_normalize(vec_sub(world->light->pos, intersection.point));
		if (!find_path(shadow_ray, world).hit) {
			double light_dist = vec_length(vec_sub(world->light->pos, intersection.point));
			double attenuation = 1.0 / (light_dist * light_dist); // Inverse square law
			double cos_theta_s = fmax(0.0, vec_dot(intersection.norm, shadow_ray.dest));
			t_rgb light_contribution = color_scalar(world->light->color, cos_theta_s * attenuation * world->light->brightness);
			return_color = color_add(return_color, light_contribution);
		}

		// Indirect lighting
			// Adding the color return of the recursively shot ray and adding up the values then scaling with BRDF
	return_color = color_scalar(color_add(return_color, return_color), BRDF * cos_theta / PI );

 */
	//return (return_color);
}


// Main function for rendering the screen for each frame called by mlx_loop_hook
int	render(t_main *main)
{
	static int	static_sample = 1;
	t_ray	ray;
	t_rgb	**output;
	t_world	*world;
	int		output_color;
	int		x;
	int		y;

	output = main->output;
	world = main->world;
	x = 0;
	y = 0;
	//int	static_sample = 1;
	while(static_sample < 2)
	{
		while (y < main->height)
		{
			while (x < main->width)
			{
				// Initializes the position of the first ray from the camera to static_sample into trace_path later
				ray = gen_ray(main->world->cam, x, y);

				// sampleses in trace_path function to shoot rays and get the result of the ray bounces back
				output[y][x] = trace_path(world, ray, 1);
				//color_scalar_div(trace_path(world, ray, 1), static_sample);
				//color_scalar_div(color_add(output[y][x], trace_path(world, ray, 1)), static_sample);

				// Packs color into ARGB format for mlx_pixel_put
				output_color = pack_color(output[y][x].r, output[y][x].g, output[y][x].b);

				mlx_pixel_put(main->mlx, main->win, x, y, output_color);
				// Refreshing to screen to black
				// output[y][x] = ret_color(0, 0, 0);
				x++;
			}
			x = 0;
			y++;
		}
		y = 0;
		static_sample++;
		printf("frame: %i\n", static_sample);
	}
	return (0);
}

int	main_pipeline(t_main *main)
{
	// Call render() function each frame with mlx_loop while handling input
	mlx_loop_hook(main->mlx, render, main);
	//render(main);
	// Take input
	key_handles(main);
	mlx_loop(main->mlx);
	return (0);
}