/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:44:23 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 13:48:13 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"
#include <fcntl.h>
#include <stdlib.h>

int	terminate(char *reason)
{
	ft_putendl(reason);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_fdf	*fdf;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0 || !read_file(fd, &map))
			return (terminate("error: invalid file"));
		fdf = init(ft_strjoin("FdF - ", argv[1]));
		if (fdf == NULL)
			return (terminate("error: mlx couldn't init"));
		fdf->map = map;
		draw(fdf);
		events(fdf);
		mlx_loop(fdf->mlx);
	}
	else
		return (terminate("error: not enough arguments"));
	return (0);
}
