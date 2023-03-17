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

int	main(int argc, char const *argv[])
{
	t_lem_in	data;
	t_room		rooms[8];
	t_link		links[100];
	int			links_count;

	(void)argc;
	(void)argv;
	links_count = 0;
	rooms[0] = create_room("0", 0, 0);
	rooms[1] = create_room("1", 1, 1);
	rooms[2] = create_room("2", 2, 2);
	rooms[3] = create_room("3", 3, 3);
	rooms[4] = create_room("4", 4, 4);
	rooms[5] = create_room("5", 5, 5);
	rooms[6] = create_room("6", 6, 6);
	rooms[7] = create_room("7", 7, 7);
	init_link(links + links_count++, rooms + 7, rooms + 2);
	init_link(links + links_count++, rooms + 1, rooms + 2);
	init_link(links + links_count++, rooms + 0, rooms + 1);
	init_link(links + links_count++, rooms + 4, rooms + 2);
	init_link(links + links_count++, rooms + 1, rooms + 5);
	init_link(links + links_count++, rooms + 0, rooms + 4);
	init_link(links + links_count++, rooms + 6, rooms + 3);
	init_link(links + links_count++, rooms + 5, rooms + 6);
	init_link(links + links_count++, rooms + 0, rooms + 7);
	init_link(links + links_count++, rooms + 2, rooms + 3);
	data.ants = 3;
	data.rooms = rooms;
	data.links = links;
	data.rooms_len = 8;
	data.links_len = links_count;
	data.start = rooms + 0;
	data.end = rooms + 3;
	lst_init(&data.best, (t_consumer)free);
	data.best_score = -1;
	data.checks = fmini3(data.ants,
			data.start->links.size, data.end->links.size);
	if (lem_in(&data) && data.best_score != -1)
		print_result(&data);
	else
		ft_putendl("ERROR");
	clean(&data);
	return (0);
}
