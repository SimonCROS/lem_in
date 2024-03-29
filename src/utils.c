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

char	create_room(char *name, int x, int y, t_room **room)
{
	*room = malloc(sizeof(t_room));
	if (!*room)
		return (FALSE);
	(*room)->name = name;
	(*room)->x = x;
	(*room)->y = y;
	(*room)->ant = 0;
	(*room)->used = FALSE;
	lst_init(&(*room)->links, NULL);
	return (TRUE);
}

char	create_link(t_room *left, t_room *right, t_link **link)
{
	*link = malloc(sizeof(t_link));
	if (!*link)
		return (FALSE);
	(*link)->mask = LINK_NONE;
	(*link)->left = left;
	(*link)->right = right;
	if (!lst_unshift(&left->links, *link)
		|| !lst_unshift(&right->links, *link))
	{
		free(*link);
		return (FALSE);
	}
	return (TRUE);
}

void	reset_datas(t_lem_in *data)
{
	t_iterator	it;
	t_link		*link;
	t_room		*room;

	it = iterator_new(&data->links);
	while (iterator_has_next(&it))
	{
		link = (t_link *)iterator_next(&it);
		if (link->mask != LINK_BOTH)
			link->mask = LINK_NONE;
	}
	it = iterator_new(&data->rooms);
	while (iterator_has_next(&it))
	{
		room = (t_room *)iterator_next(&it);
		room->used = FALSE;
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
