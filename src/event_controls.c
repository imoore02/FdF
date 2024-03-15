/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:42:04 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:42:06 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "controls.h"
#include <stdlib.h>

int	esc_n_quit(void *param)
{
	(void)param;
	exit(0);
}

void	events(t_fdf *fdf)
{
	mlx_key_hook(fdf->window, hook_key_press, fdf);
	mlx_hook(fdf->window, 17, 0, esc_n_quit, fdf);
	mlx_hook(fdf->window, 4, 0, hook_mouse_press, fdf);
	mlx_hook(fdf->window, 5, 0, hook_mouse_release, fdf);
	mlx_hook(fdf->window, 6, 0, hook_mouse_move, fdf);
}
