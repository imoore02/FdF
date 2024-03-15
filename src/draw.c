/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:34:12 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:41:18 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "libft.h"
#include <stdio.h>

int	clerp(int c1, int c2, double p)
{
	int	r;
	int	g;
	int	b;

	if (c1 == c2)
		return (c1);
	r = ft_lerpi((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	g = ft_lerpi((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	b = ft_lerpi(c1 & 0xFF, c2 & 0xFF, p);
	return (r << 16 | g << 8 | b);
}

int	line_process_point(t_fdf *fdf, t_line *l, t_vector *p1,
		t_vector *p2)
{
	double	percent;

	if (p1->x < 0 || p1->x >= WIN_WIDTH || p1->y < 0 || p1->y >= WIN_HEIGHT
		|| p2->x < 0 || p2->x >= WIN_WIDTH || p2->y < 0 || p2->y >= WIN_HEIGHT)
		return (1);
	percent = (l->dx > l->dy ?
			ft_ilerp((int)p1->x, (int)l->start.x, (int)l->stop.x)
			: ft_ilerp((int)p1->y, (int)l->start.y, (int)l->stop.y));
	image_set_pixel(fdf->image, (int)p1->x, (int)p1->y, clerp(p1->color,
			p2->color, percent));
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

//Takes 2 points (vector p1 and vector p2) and connects them (bresenham algo):
//Note: typecast as int because they are otherwise floats and they need to be
//  rounded for pixels to be put in the right spot
void	line(t_fdf *fdf, t_vector p1, t_vector p2)
{
	t_line	line;

	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	line.start = p1;
	line.stop = p2;
	line.dx = (int)ft_abs((int)p2.x - (int)p1.x);
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	line.dy = (int)ft_abs((int)p2.y - (int)p1.y);
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		if (line_process_point(fdf, &line, &p1, &p2))
			break ;
}

//Draw/projects the map:
//(1) declare t_map *map to use its values -> set it to the map 
//  element of t_fdf *fdf;
//(2) clear the image (bzero the image (which is basically a char *));
//(3) LOOP move through x (across the x axis) while it is less than 
//    the width (width of the .fdf map);
//(3.1) LOOP move through y (across y axis) while it is less than the height;
//(3.1.1) set t_vector v as a particular set of TRANSFORMED values 
//        (transformed by project_vector);
//(3.1.2) pixel puts the line (using bresenham algo) and puts into into the
//        char *image; moves through 
//       each point connecting it the the point next to it on the x axis 
//       (x + 1), and the point below it on the y axis (y + 2)
void	draw(t_fdf *fdf)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;

	map = fdf->map;
	clear_image(fdf->image);
	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			v = project_vector(vector_at(map, x, y), fdf);
			if (x + 1 < map->width)
				line(fdf, v, project_vector(vector_at(map, x + 1, y), fdf));
			if (y + 1 < map->height)
				line(fdf, v, project_vector(vector_at(map, x, y + 1), fdf));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, 0, 0);
}
