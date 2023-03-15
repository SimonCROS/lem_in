#include "lem_in.h"

static t_room	*try_get_dest(t_link *link, t_room *src, t_link **cross)
{
	if (link->left == src)
	{
		if (!link->left_valid)
			*cross = link;
		else if (link->right_valid)
			return link->right;
	}
	if (link->right == src)
	{
		if (!link->right_valid)
			*cross = link;
		else if (link->left_valid)
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
	if (!clst_push(&open, start))
	{
		clst_clear(&open);
		return FAIL;
	}

	while (open.size)
	{
		current = clst_shift(&open);
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
			if (!clst_push(&open, child))
			{
				clst_clear(&open);
				return FAIL;
			}
		}
	}
	return FALSE;
}
