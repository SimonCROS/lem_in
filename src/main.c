/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	get_score(int ants, t_list *paths, int *max)
{
	t_int_tuple	*costs;
	t_iterator	it;
	t_int_tuple	min;
	int			i;

	costs = ft_calloc(paths->size, sizeof(t_int_tuple));
	if (!costs)
		return (FALSE);
	it = iterator_new(paths);
	i = 0;
	while (iterator_has_next(&it))
		costs[i++].l = ((t_list *)iterator_next(&it))->size;
	*max = -1;
	while (ants-- > 0)
	{
		min = costs[0];
		i = 0;
		while (++i < paths->size)
			if (min.l + min.r > costs[i].l + costs[i].r)
				min = costs[i];
		min.r += 1;
		*max = ft_ternary(*max < min.l + min.r, min.l + min.r, *max);
	}
	free(costs);
	return (TRUE);
}

static void	disable_link_to(t_room *room)
{
	t_iterator	it;
	t_link		*link;

	if (room->parent)
	{
		it = iterator_new(&room->parent->links);
		while (iterator_has_next(&it))
		{
			link = (t_link *)iterator_next(&it);
			if (link->left == room)
				link->mask = LINK_LEFT;
			if (link->right == room)
				link->mask = LINK_RIGHT;
		}
	}
}

static t_list	*build_path_from_parents(t_room *last)
{
	t_list		*path;
	t_room		*current;

	path = lst_new(NULL);
	if (!path)
		return (NULL);
	current = last;
	while (current)
	{
		if (!lst_unshift(path, current))
		{
			lst_destroy(path);
			return (NULL);
		}
		disable_link_to(current);
		current = current->parent;
	}
	return (path);
}

static char	get_path_group(t_lem_in *data, t_list *results, int *results_score)
{
	t_link		*cross;
	t_list		*path;
	int			i;
	int			score;

	lst_init(results, (t_consumer)lst_destroy);
	*results_score = -1;
	while (TRUE)
	{
		if (results->size >= data->checks)
			break ;
		i = 0;
		while (i < data->rooms_len)
		{
			data->rooms[i].selected = FALSE;
			data->rooms[i].parent = NULL;
			i++;
		}
		if (bfs(data->start, data->end, &cross))
		{
			path = build_path_from_parents(data->end);
			if (!path || !lst_unshift(results, path)
				|| !get_score(data->ants, results, &score))
			{
				lst_clear(results);
				return (FALSE);
			}
			if (score < *results_score || *results_score == -1)
			{
				*results_score = score;
			}
			else
				break ;
		}
		else
		{
			if (cross)
				cross->mask = LINK_BOTH;
			cross = NULL;
			break ;
		}
	}
	return (TRUE);
}

static void	reset_links(t_lem_in *data)
{
	int		i;

	i = 0;
	while (i < data->links_len)
	{
		if (data->links[i].mask != LINK_BOTH)
			data->links[i].mask = LINK_NONE;
		i++;
	}
}

static char	alloc_error(t_lem_in *data, t_list *results)
{
	lst_clear(&data->best);
	lst_clear(results);
	return (FALSE);
}

char	lem_in(t_lem_in *data)
{
	t_list	results;
	int		results_score;

	lst_init(&data->best, (t_consumer)lst_destroy);
	data->best_score = -1;
	data->checks = fmini3(data->ants,
			data->start->links.size, data->end->links.size);
	while (TRUE)
	{
		reset_links(data);
		if (!get_path_group(data, &results, &results_score))
			return (alloc_error(data, &results));
		if (results_score != -1
			&& (results_score < data->best_score || data->best_score == -1))
		{
			lst_clear(&data->best);
			if (!lst_copy_to(&results, &data->best))
				return (alloc_error(data, &results));
			data->best_score = results_score;
		}
		else
			break ;
	}
	return (TRUE);
}

int	main(int argc, char const *argv[])
{
	// t_room rooms[6] = {
	// 	(t_room){.name = "0"},
	// 	(t_room){.name = "1"},
	// 	(t_room){.name = "2"},
	// 	(t_room){.name = "3"},
	// 	(t_room){.name = "4"},
	// 	(t_room){.name = "5"},
	// };
	// t_link links[7] = {
	// 	(t_link){.left = rooms + 0, .right = rooms + 4, .mask = 0},
	// 	(t_link){.left = rooms + 0, .right = rooms + 1, .mask = 0},
	// 	(t_link){.left = rooms + 4, .right = rooms + 2, .mask = 0},
	// 	(t_link){.left = rooms + 1, .right = rooms + 2, .mask = 0},
	// 	(t_link){.left = rooms + 1, .right = rooms + 5, .mask = 0},
	// 	(t_link){.left = rooms + 2, .right = rooms + 3, .mask = 0},
	// 	(t_link){.left = rooms + 5, .right = rooms + 3, .mask = 0},
	// };

	// lst_init(&rooms[0].links, NULL);
	// lst_init(&rooms[1].links, NULL);
	// lst_init(&rooms[2].links, NULL);
	// lst_init(&rooms[3].links, NULL);
	// lst_init(&rooms[4].links, NULL);
	// lst_init(&rooms[5].links, NULL);

	// lst_unshift(&rooms[0].links, links + 0);
	// lst_unshift(&rooms[4].links, links + 0);
	// lst_unshift(&rooms[0].links, links + 1);
	// lst_unshift(&rooms[1].links, links + 1);
	// lst_unshift(&rooms[4].links, links + 2);
	// lst_unshift(&rooms[2].links, links + 2);
	// lst_unshift(&rooms[1].links, links + 3);
	// lst_unshift(&rooms[2].links, links + 3);
	// lst_unshift(&rooms[1].links, links + 4);
	// lst_unshift(&rooms[5].links, links + 4);
	// lst_unshift(&rooms[2].links, links + 5);
	// lst_unshift(&rooms[3].links, links + 5);
	// lst_unshift(&rooms[5].links, links + 6);
	// lst_unshift(&rooms[3].links, links + 6);

	// t_lem_in data = {
	// 	.ants = 2,
	// 	.rooms = rooms,
	// 	.links = links,
	// 	.rooms_len = 6,
	// 	.links_len = 7,
	// 	.start = rooms + 0,
	// 	.end = rooms + 3,
	// };
	// lem_in(&data);

	// t_iterator it1 = iterator_new(&data.best);
	// while (iterator_has_next(&it1))
	// {
	// 	ft_putendl("---------------------");
	// 	t_iterator it2 = iterator_new(((t_list *)iterator_next(&it1)));
	// 	while (iterator_has_next(&it2))
	// 	{
	// 		ft_putendl(((t_room *)iterator_next(&it2))->name);
	// 	}
	// }
    int        fd;
    char    *line;

    line = NULL;
    fd = open("test", O_RDWR);
    if (fd < 0)
    {
        write(2, "Error opening file\n", 19);
        exit(1);
    }
    while(ft_get_next_line(fd, 100, &line))
    {
        write(1, line, ft_strlen(line));
        free(line);
    }
    write(1, line, ft_strlen(line));
    free(line);
	return (0);
}
