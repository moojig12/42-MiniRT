/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:55:15 by nmandakh          #+#    #+#             */
/*   Updated: 2024/12/10 13:56:31 by nmandakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_main	*screen_init_thread(t_thread_screen *screen, t_render *thread)
{
	screen->x = 0;
	screen->y = 0;
	screen->y_limit = thread->main->height / THREAD_COUNT;
	if (thread->id != 1)
	{
		screen->y = 0 + (thread->main->height / thread->id);
		screen->y_limit = (screen->y_limit * thread->id);
	}
	return (thread->main);
}

void	thread_inner_render(t_main *main, t_rgb **output, int x, int y)
{
	if (main->render_switch == HIGH)
		render_super(main, x, y, output);
	else
		render_low(main, x, y, output);
	put_color_to_buff(main, output, x, y);
}

void	initiate_mutexes(t_main *main)
{
	int	y;

	y = 0;
	main->thread = malloc(THREAD_COUNT * sizeof(t_render));
	pthread_mutex_init(&main->write_lock, NULL);
	main->output_pixel = (pthread_mutex_t *)malloc(main->height \
	* sizeof(pthread_mutex_t));
	while (y < THREAD_COUNT)
	{
		pthread_mutex_init(&main->output_pixel[y], NULL);
		main->thread[y].id = y + 1;
		main->thread[y].main = main;
		main->thread[y].world = main->world;
		main->thread[y].image_ptr = main->img;
		main->thread[y].render_lock = main->output_pixel;
		main->thread[y].write_lock = &main->write_lock;
		y++;
	}
}
