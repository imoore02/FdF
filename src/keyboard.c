/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:52:59 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:53:00 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "controls.h"
#include <stdlib.h>

int	hook_key_press(int key, t_fdf *fdf)
{
	(void)fdf;
	if (key == MAIN_PAD_ESC)
		exit(EXIT_SUCCESS);
	if (key == MAIN_PAD_PLUS
		|| key == MAIN_PAD_MINUS)
		zoom(key, fdf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		move(key, fdf);
	return (0);
}

void	zoom(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_PLUS
		|| key == MOUSE_SCROLL_UP)
		fdf->cam->scale += 1;
	else if (key == MAIN_PAD_MINUS
		|| key == MOUSE_SCROLL_DOWN)
		fdf->cam->scale -= 1;
	if (fdf->cam->scale < 1)
		fdf->cam->scale = 1;
	mlx_clear_window(fdf->mlx, fdf->window);
	draw(fdf);
}

//shifts map up down side to side w arrow keys
void	move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->cam->offsetx -= 10;
	else if (key == ARROW_RIGHT)
		fdf->cam->offsetx += 10;
	else if (key == ARROW_UP)
		fdf->cam->offsety -= 10;
	else if (key == ARROW_DOWN)
		fdf->cam->offsety += 10;
	mlx_clear_window(fdf->mlx, fdf->window);
	draw(fdf);
}
