/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*try_get_dest(t_link *link, t_room *src, t_link **cross)
{
	if (link->left == src)
	{
		if (link->mask & LINK_LEFT)
			*cross = link;
		else if (!(link->mask & LINK_RIGHT))
			return (link->right);
	}
	if (link->right == src)
	{
		if (link->mask & LINK_RIGHT)
			*cross = link;
		else if (!(link->mask & LINK_LEFT))
			return (link->left);
	}
	return (NULL);
}

char	bfs(t_room *start, t_room *goal, t_link **cross)
{
	t_room		*current;
	t_room		*child;
	t_clist		open;
	t_iterator	it;

	*cross = NULL;
	clst_init(&open, NULL);
	clst_push(&open, start);
	while (open.size)
	{
		current = (t_room *)clst_shift(&open);
		if (current == goal)
			return (TRUE);
		it = iterator_new(&current->links);
		while (iterator_has_next(&it))
		{
			child = try_get_dest((t_link *)iterator_next(&it), current, cross);
			if (!child || child->dist != 0 || child == start)
				continue ;
			child->dist = current->dist + 1;
			child->parent = current;
			clst_push(&open, child);
		}
	}
	return (FALSE);
}
