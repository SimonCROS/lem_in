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

static void	check_cross(t_room *src, t_link **cross)
{
	t_iterator	it;
	t_link		*link;

	it = iterator_new(&src->links);
	while (iterator_has_next(&it))
	{
		link = (t_link *)iterator_next(&it);
		if (link->left == src && link->mask & LINK_LEFT)
			*cross = link;
		if (link->right == src && link->mask & LINK_RIGHT)
			*cross = link;
	}
}

static t_room	*try_get_dest(t_link *link, t_room *src)
{
	if (link->left == src && !(link->mask & LINK_RIGHT))
		return (link->right);
	if (link->right == src && !(link->mask & LINK_LEFT))
		return (link->left);
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
			child = try_get_dest((t_link *)iterator_next(&it), current);
			if (!child || child->dist != 0 || child == start)
				continue ;
			if (child->used && child != goal)
			{
				check_cross(child, cross);
				continue ;
			}
			child->dist = current->dist + 1;
			child->parent = current;
			clst_push(&open, child);
		}
	}
	return (FALSE);
}
