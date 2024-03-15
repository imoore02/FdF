/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:53:54 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:54:36 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	fill_colors(t_map *m)
{
	t_vector	v;
	t_vector	*cur;

	v.y = 0;
	while (v.y < m->height)
	{
		v.x = 0;
		while (v.x < m->width)
		{
			cur = m->vectors[(int)v.y * m->width + (int)v.x];
			cur->color = clerp(0xC000FF, 0x4DFFD9, ft_ilerp(cur->z,
						m->depth_min, m->depth_max));
			v.x++;
		}
		v.y++;
	}
}

//Transforms the values of t_vector v:
//(1) AXIS/POINT ROTATION - without changing this it would rotate 
//    around the first point and first point would go right in 
//    the middle of the screen
//(2) rotate?
//(3) ZOOM - connect to + and - buttons - multiply vectors by a 'scale'
//(4) PUT STARTING POINT IN CENTRE (othewise it would be in the corner
//    of the screen)

t_vector	project_vector(t_vector v, t_fdf *fdf)
{
	v.x -= (fdf->map->width) / 2;
	v.y -= (fdf->map->height) / 2;
	v.z -= (fdf->map->depth_min + fdf->map->depth_max) / 2;
	v = rotate(v, fdf->cam);
	v.x *= fdf->cam->scale;
	v.y *= fdf->cam->scale;
	v.x += fdf->cam->offsetx;
	v.y += fdf->cam->offsety;
	return (v);
}

//Find the vector located at ((y * map->width) + x):
//Note: not a double array so its going to move through 
//  the lines y times, and then move x places more;
t_vector	vector_at(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
}

t_vector	*get_vector(int x, int y, char *str)
{
	t_vector	*v;

	v = ft_memalloc(sizeof(t_vector));
	if (v == NULL)
		return (NULL);
	v->x = (double)x;
	v->y = (double)y;
	v->z = (double)ft_atoi(str);
	v->color = 0xFFFFFF;
	return (v);
}

t_map	*map_init(int width, int height)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->depth_min = 0;
	map->depth_max = 0;
	map->vectors = ft_memalloc(sizeof(t_vector *) * width * height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}
