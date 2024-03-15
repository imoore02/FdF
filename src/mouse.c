/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:54:50 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:55:14 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	hook_mouse_press(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	if (y < 0)
		return (0);
	fdf->mouse->isdown |= 1 << button;
	return (0);
}

int	hook_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	fdf->mouse->isdown &= ~(1 << button);
	return (0);
}

int	hook_mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse->lastx = fdf->mouse->x;
	fdf->mouse->lasty = fdf->mouse->y;
	fdf->mouse->x = x;
	fdf->mouse->y = y;
	if (fdf->mouse->isdown & (1 << 1) && fdf->mouse->isdown & (1 << 2))
	{
		fdf->cam->offsetx += (x - fdf->mouse->lastx);
		fdf->cam->offsety += (y - fdf->mouse->lasty);
	}
	else if (fdf->mouse->isdown & (1 << 1))
	{
		fdf->cam->x += (fdf->mouse->lasty - y) / 200.0f;
		fdf->cam->y -= (fdf->mouse->lastx - x) / 200.0f;
	}
	else if (fdf->mouse->isdown & (1 << 2))
	{
		fdf->cam->scale += (fdf->mouse->lasty - y) / 10.0f + 0.5f;
		if (fdf->cam->scale < 1)
			fdf->cam->scale = 1;
	}
	if (fdf->mouse->isdown)
		draw(fdf);
	return (0);
}

t_vector	rotate(t_vector p, t_cam *r)
{
	t_vector	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(r->y) * x + sin(r->y) * z;
	v.z = -sin(r->y) * x + cos(r->y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(r->x) * y - sin(r->x) * z;
	v.z = sin(r->x) * y + cos(r->x) * z;
	v.color = p.color;
	return (v);
}
