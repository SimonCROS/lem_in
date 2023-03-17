/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	create_room(char *name, int x, int y)
{
	t_room	room;

	room.name = name;
	room.x = x;
	room.y = y;
	room.ant = 0;
	lst_init(&room.links, NULL);
	return (room);
}

char	init_link(t_link *link, t_room *left, t_room *right)
{
	link->mask = LINK_NONE;
	if (!lst_unshift(&left->links, link))
		return (FALSE);
	link->left = left;
	if (!lst_unshift(&right->links, link))
		return (FALSE);
	link->right = right;
	return (TRUE);
}

void	reset_links(t_lem_in *data)
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

void	disable_link(t_room *from, t_room *to)
{
	t_iterator	it;
	t_link		*link;

	if (from)
	{
		it = iterator_new(&from->links);
		while (iterator_has_next(&it))
		{
			link = (t_link *)iterator_next(&it);
			if (link->left == to)
				link->mask = LINK_LEFT;
			if (link->right == to)
				link->mask = LINK_RIGHT;
		}
	}
}

char	clear_ret_false(t_list *results)
{
	lst_clear(results);
	return (FALSE);
}
