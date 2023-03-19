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

static void	del_room(t_room *room)
{
	if (room)
	{
		lst_clear(&room->links);
		free(room);
	}
}

static void	clean(t_lem_in *data)
{
	int	line;

	line = 0;
	lst_clear(&data->best);
	lst_clear(&data->rooms);
	lst_clear(&data->links);
	hashmap_free(&data->rooms_names);
	while (data->lines && data->lines[line])
		free(data->lines[line++]);
	free(data->lines);
}

int	main(int argc, char **argv)
{
	t_lem_in	data;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl("ERROR");
		return (1);
	}
	data.best_score = -1;
	data.start = NULL;
	data.end = NULL;
	data.ants = -1;
	data.lines = NULL;
	lst_init(&data.best, (t_con)free);
	lst_init(&data.rooms, (t_con)del_room);
	lst_init(&data.links, (t_con)free);
	if (hashmap_init(&data.rooms_names)
		&& parser(&data)
		&& lem_in(&data)
		&& data.best_score != -1)
		print_result(&data);
	else
		ft_putendl("ERROR");
	clean(&data);
	return (0);
}
