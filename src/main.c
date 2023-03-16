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

	rooms[0] = (t_room){.name = "0"};
	rooms[1] = (t_room){.name = "1"};
	rooms[2] = (t_room){.name = "2"};
	rooms[3] = (t_room){.name = "3"};
	rooms[4] = (t_room){.name = "4"};
	rooms[5] = (t_room){.name = "5"};
	links[0] = (t_link){.left = rooms + 0, .right = rooms + 4, .mask = 0};
	links[1] = (t_link){.left = rooms + 0, .right = rooms + 1, .mask = 0};
	links[2] = (t_link){.left = rooms + 4, .right = rooms + 2, .mask = 0};
	links[3] = (t_link){.left = rooms + 1, .right = rooms + 2, .mask = 0};
	links[4] = (t_link){.left = rooms + 1, .right = rooms + 5, .mask = 0};
	links[5] = (t_link){.left = rooms + 2, .right = rooms + 3, .mask = 0};
	links[6] = (t_link){.left = rooms + 5, .right = rooms + 3, .mask = 0};
	lst_init(&rooms[0].links, NULL);
	lst_init(&rooms[1].links, NULL);
	lst_init(&rooms[2].links, NULL);
	lst_init(&rooms[3].links, NULL);
	lst_init(&rooms[4].links, NULL);
	lst_init(&rooms[5].links, NULL);
	lst_unshift(&rooms[0].links, links + 0);
	lst_unshift(&rooms[4].links, links + 0);
	lst_unshift(&rooms[0].links, links + 1);
	lst_unshift(&rooms[1].links, links + 1);
	lst_unshift(&rooms[4].links, links + 2);
	lst_unshift(&rooms[2].links, links + 2);
	lst_unshift(&rooms[1].links, links + 3);
	lst_unshift(&rooms[2].links, links + 3);
	lst_unshift(&rooms[1].links, links + 4);
	lst_unshift(&rooms[5].links, links + 4);
	lst_unshift(&rooms[2].links, links + 5);
	lst_unshift(&rooms[3].links, links + 5);
	lst_unshift(&rooms[5].links, links + 6);
	lst_unshift(&rooms[3].links, links + 6);
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
	lem_in(&data);
	it1 = iterator_new(&data.best);
	while (iterator_has_next(&it1))
	{
		ft_putendl("---------------------");
		it2 = iterator_new(((t_list *)iterator_next(&it1)));
		while (iterator_has_next(&it2))
		{
			ft_putendl(((t_room *)iterator_next(&it2))->name);
		}
	}
	clean(&data);
	return (0);
}
