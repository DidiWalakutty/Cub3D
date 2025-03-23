/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasamankarimi <yasamankarimi@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:22:43 by yasamankari       #+#    #+#             */
/*   Updated: 2025/03/23 12:23:57 by yasamankari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
