/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:33:25 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 14:19:01 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH			1280
# define WIN_HEIGHT			720

typedef struct s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
	double		**matrix;
}					t_cam;
typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vector;
typedef struct s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
}					t_map;
typedef struct s_mouse
{
	char		isdown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}					t_mouse;
typedef struct s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_image;
typedef struct s_fdf
{
	void		*mlx;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_cam		*cam;
	t_mouse		*mouse;
	double		**zbuf;
}					t_fdf;
typedef struct s_line
{
	t_vector	start;
	t_vector	stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_line;
int					read_file(int fd, t_map **map);
t_vector			*get_vector(int x, int y, char *str);
t_map				*map_init(int width, int height);
t_fdf				*init(char *title);
void				draw(t_fdf *fdf);
t_vector			rotate(t_vector p, t_cam *r);
t_vector			vector_at(t_map *map, int x, int y);
t_vector			project_vector(t_vector p, t_fdf *fdf);
int					hook_mouse_move(int x, int y, t_fdf *fdf);
int					hook_mouse_press(int button, int x, int y, t_fdf *fdf);
int					hook_mouse_release(int button, int x, int y, t_fdf *fdf);
int					hook_key_press(int key, t_fdf *fdf);
void				image_set_pixel(t_image *image, int x, int y, int color);
void				clear_image(t_image *image);
t_image				*new_image(t_fdf *fdf);
t_image				*del_image(t_fdf *fdf, t_image *img);
void				fill_colors(t_map *m);
void				events(t_fdf *fdf);
void				zoom(int key, t_fdf *fdf);
void				move(int key, t_fdf *fdf);
int					clerp(int c1, int c2, double p);
void				find_depth(t_map *m);
void				other(t_map **m);
#endif