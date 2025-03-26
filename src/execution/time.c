/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/23 12:22:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2025/03/26 12:55:24 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fps_hook(void *param)
{
	static uint32_t	fps;
	t_cub3d			*meta;

	meta = param;
	if (!(meta->fps_timer.time_func))
	{
		fps = 0;
		timer_init(&meta->fps_timer, mlx_get_time);
	}
	if (timer_delta(&meta->fps_timer) >= 1)
	{
		meta->fps = fps;
		printf("FPS: [%u]\n", meta->fps);
		timer_start(&meta->fps_timer);
		fps = 0;
	}
	else
		fps++;
}

t_timer	*timer_init(t_timer *t, double (*time_func)(void))
{
	t->time_func = time_func;
	return (t);
}

double	timer_start(t_timer *t)
{
	t->start = (*t->time_func)();
	return (t->start);
}

double	timer_stop(t_timer *t)
{
	t->end = (*t->time_func)();
	return (t->end);
}

double	timer_delta(t_timer *t)
{
	timer_stop(t);
	t->delta = t->end - t->start;
	return (t->delta);
}
