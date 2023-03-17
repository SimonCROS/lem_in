/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_rooms(t_lem_in *data)
{
	int		i;
	t_room	*room;

	i = 0;
	while (i < data->rooms_len)
	{
		room = data->rooms + i;
		if (room == data->start)
			ft_putendl("##start");
		if (room == data->end)
			ft_putendl("##end");
		ft_putstr(room->name);
		ft_putstr(" ");
		ft_putnbr(room->x);
		ft_putstr(" ");
		ft_putnbr(room->y);
		ft_putendl("");
		i++;
	}
}

static void	print_links(t_lem_in *data)
{
	int		i;
	t_link	*link;

	i = 0;
	while (i < data->links_len)
	{
		link = data->links + i;
		ft_putstr(link->left->name);
		ft_putstr("-");
		ft_putendl(link->right->name);
		i++;
	}
}

static void	print_steps(t_lem_in *data)
{
	t_iterator	it;
	t_path		*path;
	int			i;

	get_score(data->ants, &data->best);
	it = iterator_new(&data->best);
	while (iterator_has_next(&it))
	{
		ft_putstr("[");
		path = (t_path *)iterator_next(&it);
		i = 0;
		while (i < path->len)
		{
			ft_putstr(path->rooms[i++]->name);
			if (i < path->len)
				ft_putstr(", ");
		}
		ft_putstr("] -> ");
		ft_putnbr(path->ants);
		ft_putendl(" ants");
	}
	return ;
}

void	print_result(t_lem_in *data)
{
	ft_putnbr(data->ants);
	ft_putendl("");
	print_rooms(data);
	print_links(data);
	ft_putendl("");
	if (data->best_score == -1)
	{
		ft_putendl("No path were found.");
		return ;
	}
	print_steps(data);
}
