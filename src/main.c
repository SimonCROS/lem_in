#include "lem_in.h"

static int	get_score(int ants, t_list *paths)
{
	// TODO
	return 1;
}

void	lem_in(int ants, t_room *start, t_room *end, t_room *rooms, t_link *links, int rooms_len, int links_len)
{
	int		checks;
	t_list	best;
	int		best_score;
	t_list	results;
	int		results_score;
	t_link	*cross;
	int		i;
	t_room	*current;
	t_list	*path;

	lst_init(&best, lst_destroy);
	best_score = -1;
	checks = fmini3(ants, start->links.size, end->links.size);
	while (TRUE)
	{
		lst_init(&results, lst_destroy);
		results_score = -1;

		i = 0;
		while (i < links_len)
		{
			if (links[i].mask != LINK_BOTH)
				links[i].mask = LINK_NONE;
			i++;
		}

		while (TRUE)
		{
			if (results.size >= checks)
				break;

			i = 0;
			while (i < rooms_len)
			{
				rooms[i].selected = FALSE;
				i++;
			}

			if (bfs(start, end, &cross))
			{
				path = lst_new(NULL);
				if (!path)
				{
					// TODO free
				}
				current = end;
				while (current)
				{
					if (!lst_unshift(&path, current))
					{
						// TODO free
					}
					if (current->parent)
					{
						t_iterator	it = iterator_new(&current->parent->links);
						while (iterator_has_next(&it))
						{
							t_link *link = (t_link *)iterator_next(&it);
							if (link->left == current)
								link->mask = LINK_LEFT;
							if (link->right == current)
								link->mask = LINK_RIGHT;
						}
					}
					current = end->parent;
				}
				if (!lst_unshift(&results, path))
				{
					// TODO free
				}
				int	score = get_score(ants, &results);
				if (score < results_score || results_score == -1)
				{
					results_score = score;
				}
				else
					break;
			}
			else
			{
				if (cross)
					cross->mask = LINK_BOTH;
				cross = NULL;
				break;
			}

			if (results_score != -1 && (results_score < best_score || best_score == -1))
			{
				lst_clear(&best);
				best = results;
				best_score = results_score;
			}
			else
				break;
		}
	}
}

int		main(int argc, char const *argv[])
{
	return 0;
}
