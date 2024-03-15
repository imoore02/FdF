#include "libft.h"
#include "fdf.h"
#include "mlx.h"

t_fdf		*fdfdel(t_fdf *fdf)
{
	if (fdf->window != NULL)
		mlx_destroy_window(fdf->mlx, fdf->window);
	if (fdf->cam != NULL)
		ft_memdel((void **)&fdf->cam);
	if (fdf->mouse != NULL)
		ft_memdel((void **)&fdf->mouse);
	if (fdf->image != NULL)
		del_image(fdf, fdf->image);
	ft_memdel((void **)&fdf);
	return (NULL);
}

t_fdf	*init(char *title)
{
	t_fdf	*fdf;

	if ((fdf = ft_memalloc(sizeof(t_fdf))) == NULL)
		return (NULL);
	if ((fdf->mlx = mlx_init()) == NULL
		|| (fdf->window = mlx_new_window(fdf->mlx, WIN_WIDTH,
			WIN_HEIGHT, title)) == NULL
		|| (fdf->cam = ft_memalloc(sizeof(t_cam))) == NULL
		|| (fdf->mouse = ft_memalloc(sizeof(t_mouse))) == NULL
		|| (fdf->image = new_image(fdf)) == NULL)
		return (fdfdel(fdf));
	fdf->cam->x = 0.5;
	fdf->cam->y = 0.5;
	fdf->cam->scale = 32;
	fdf->cam->offsetx = WIN_WIDTH / 2;
	fdf->cam->offsety = WIN_HEIGHT / 2;
	return (fdf);
}
