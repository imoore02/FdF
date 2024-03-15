/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 13:55:27 by imoore            #+#    #+#             */
/*   Updated: 2022/08/26 14:28:37 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "fdf.h"
#include <limits.h>



//Frees param t_list **lst and t_map **map:
//(1) LOOP moving through all elements of list and freeing them;
//(2) LOOP moving through stuff inside map and vectors to free
static int	cleanup(t_list **lst, t_map **map)
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_memdel(&(*lst)->content);
		ft_memdel((void **)lst);
		*lst = next;
	}
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	return (0);
}

//finds lines:
//(1) t_list *temp is a the first spot in a linked list - holding a void *ptr, size_t element, and void *next;
//(2) LOOP - while get_next_line exists;
//(2.1) i == 1 => first run through: find the map width (ft_countwords with 'line' (found by get_next_line) as a param, and ' ' as a delimiter);
//(2.2) sets temp element as containing char *line, and size_t (length of line + 1), and *next as NULL; MEMORY ALLOCATES FOR EACH ELEMENT;
//(2.3) if temp == NULL (ft_lstnew fails) -> cleanup
//(2.4) link temp to lst (makes temp->next point to lst) => for every loop through this list will grow and each line will become linked to the next;
//(2.5) check if width is the same for each line;
//(2.6) delete/clear &line (get_next_line does memory allocation)
//(3) if get_next_line or ft_countwords failed (=-1) -> cleanup
//(4) makes lst previous;
static int	get_lines(int fd, t_list **lst)
{
	t_list	*temp;
	int		width;
	char	*line;
	int		i;

	while ((i = get_next_line(fd, &line)))
	{
		if (i == 1)
			width = ft_countwords(line, ' ');
		temp = ft_lstnew(line, ft_strlen(line) + 1); 
		if ((temp) == NULL)
			return (cleanup(lst, NULL));
		ft_lstadd(lst, temp);
		if (width != ft_countwords(line, ' '))
			return (cleanup(lst, NULL));
		ft_memdel((void **)&line);
	}
	if (width == -1 || i == -1) 
		return (cleanup(lst, NULL));
	ft_lstrev(lst);
	return (width);
}

void		find_depth(t_map *m)
{
	int			min;
	int			max;
	t_vector	v;
	t_vector	current;

	min = INT_MAX;
	max = INT_MIN;
	v.y = 0;
	while (v.y < m->height)
	{
		v.x = 0;
		while (v.x < m->width)
		{
			current = *m->vectors[(int)v.y * m->width + (int)v.x];
			if (current.z < min)
				min = current.z;
			if (current.z > max)
				max = current.z;
			v.x++;
		}
		v.y++;
	}
	m->depth_min = min;
	m->depth_max = max;
}

//Assigning the values from the linked list (all the lines) and putting them into the correctaing map->vector (t_vector):
static int	populate_map(t_map **m, t_list *list)
{
	t_list	*lst;
	char	**split;
	int		x;
	int		y;

	lst = list;
	y = 0;
	while (y < (*m)->height)
	{
		x = 0;
		split = ft_strsplit(lst->content, ' ');
		if (split == NULL)
			return (cleanup(&list, m));
		while (x < (*m)->width)
		{
			(*m)->vectors[y * (*m)->width + x] = get_vector(x, y, split[x]);
			x++;
		}
		ft_splitdel(&split);
		lst = lst->next;
		y++;
	}
	find_depth(*m);
	fill_colors(*m);
	cleanup(&list, NULL);
	return (1);
}

//Reads the .fdf file ->finds the width and height of the 
// graph it will produce -> memory allocates and initialises 
// it -> stores its values:
//(1) using a linked list to store all the values (t_list *lst)
//  -> initiate NULL;
//(2) get all lines/values and store them (get_lines) -> 
// return width -> if fail return 0;
//(3) initiate and memroy allocate for t_map - with height
// and width considered -> if fail cleanup;
int	read_file(int fd, t_map **m)
{
	t_list	*lst;
	int		width;

	lst = NULL;
	width = get_lines(fd, &lst);
	if (!width)
		return (0);
	*m = map_init(width, ft_lstcount(lst));
	if (*m == NULL)
		return (cleanup(&lst, m));
	return (populate_map(m, lst));
}
