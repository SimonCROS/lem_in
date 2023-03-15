#include "lem_in.h"

void	lem_in(int ants, t_room *start, t_room *end, t_room *rooms, t_link *links, int rooms_len, int links_len)
{
	int		checks;
	t_clist	best;
	int		best_score;
	t_clist	results;
	int		results_score;
	int		i;

	clst_init(&best, NULL);
	best_score = -1;
	checks = fmini3(ants, start->links.size, end->links.size);
	while (TRUE)
	{
		clst_init(&results, NULL);
		results_score = -1;

		i = 0;
		while (i < links_len)
		{
			if (links[i].mask != LINK_BOTH)
				links[i].mask = LINK_NONE;
			i++;
		}
	}
}

int		main(int argc, char const *argv[])
{
	return 0;
}
