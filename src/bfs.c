#include "lem_in.h"

static t_room	*try_get_dest(t_link *link, t_room *src, t_link **cross)
{
	if (link->left == src)
	{
		if (link->mask & LINK_LEFT)
			*cross = link;
		else if (!(link->mask & LINK_RIGHT))
			return link->right;
	}
	if (link->right == src)
	{
		if (link->mask & LINK_RIGHT)
			*cross = link;
		else if (!(link->mask & LINK_LEFT))
			return link->left;
	}
	return NULL;
}

char	bfs(t_room *start, t_room *goal, t_link **cross)
{
	t_room		*current;
	t_room		*child;
	t_clist		open;
	t_iterator	it;
	t_link		*link;

	*cross = NULL;
	clst_init(&open, NULL);
	start->selected = TRUE;
	clst_push(&open, room_to_bfs_open_entry(start));

	while (open.size)
	{
		current = bfs_open_entry_to_room(clst_shift(&open));
		if (current == goal)
			return TRUE;
		it = iterator_new(&current->links);
		while (iterator_has_next(&it))
		{
			link = (t_link *)iterator_next(&it);
			child = try_get_dest(link, current, cross);
			if (!child || child->selected)
				continue;
			child->selected = TRUE;
			child->parent = current;
			clst_push(&open, room_to_bfs_open_entry(child));
		}
	}
	return FALSE;
}
