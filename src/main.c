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

static void	clean(t_lem_in *data)
{
	int	i;

	lst_clear(&data->best);
	i = 0;
	while (i < data->rooms_len)
		lst_clear(&data->rooms[i++].links);
	//free(data->rooms);
	//free(data->links);
}

/*
	if (!lem_in(&data))
	{
		ft_putendl_fd("Marche po...", 2);
	}

	t_iterator it1 = iterator_new(&data.best);
	while (iterator_has_next(&it1))
	{
		ft_putendl("---------------------");
		t_iterator it2 = iterator_new(((t_list *)iterator_next(&it1)));
		while (iterator_has_next(&it2))
		{
			ft_putendl(((t_room *)iterator_next(&it2))->name);
		}
	}

	clean(&data);
*/
int	main(int argc, char const *argv[])
{
	t_lem_in	data;
	t_room		rooms[6];
	t_link		links[7];
	t_iterator	it1;
	t_iterator	it2;

	rooms[0] = create_room("0", 0, 0);
	rooms[1] = create_room("1", 1, 1);
	rooms[2] = create_room("2", 2, 2);
	rooms[3] = create_room("3", 3, 3);
	rooms[4] = create_room("4", 4, 4);
	rooms[5] = create_room("5", 5, 5);
	init_link(links + 0, rooms + 0, rooms + 4);
	init_link(links + 1, rooms + 0, rooms + 1);
	init_link(links + 2, rooms + 4, rooms + 2);
	init_link(links + 3, rooms + 1, rooms + 2);
	init_link(links + 4, rooms + 1, rooms + 5);
	init_link(links + 5, rooms + 2, rooms + 3);
	init_link(links + 6, rooms + 5, rooms + 3);
	data.ants = 2;
	data.rooms = rooms;
	data.links = links;
	data.rooms_len = 6;
	data.links_len = 7;
	data.start = rooms + 0;
	data.end = rooms + 3;
	lst_init(&data.best, (t_consumer)lst_destroy);
	data.best_score = -1;
	data.checks = fmini3(data.ants,
			data.start->links.size, data.end->links.size);
	if (lem_in(&data))
	{
		if (data.best_score != -1)
		{
			it1 = iterator_new(&data.best);
			while (iterator_has_next(&it1))
			{
				ft_putstr("[");
				it2 = iterator_new(((t_list *)iterator_next(&it1)));
				while (iterator_has_next(&it2))
				{
					ft_putstr(((t_room *)iterator_next(&it2))->name);
					if (iterator_has_next(&it2))
						ft_putstr(", ");
				}
				ft_putendl("]");
			}
		}
		else
		{
			ft_putendl("No path were found.");
		}
	}
	else
	{
		ft_putendl_fd("Malloc error.", 2);
	}
	clean(&data);
	return (0);
}
