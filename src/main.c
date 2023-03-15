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

static int	get_score(int ants, t_list *paths)
{
	// TODO
	return (1);
}

static void	get_next_path_group(t_lem_in *data, t_list *results, int *results_score)
{
	t_link	*cross;
	t_room	*current;
	t_list	*path;
	int		i;

	lst_init(results, (t_consumer)lst_destroy);
	*results_score = -1;
	while (TRUE)
	{
		if (results->size >= data->checks)
			break ;
		i = 0;
		while (i < data->rooms_len)
		{
			data->rooms[i].selected = FALSE;
			i++;
		}
		if (bfs(data->start, data->end, &cross))
		{
			path = lst_new(NULL);
			if (!path)
			{
				// TODO free
			}
			current = data->end;
			while (current)
			{
				if (!lst_unshift(path, current))
				{
					// TODO free
				}
				if (current->parent)
				{
					t_iterator	it = iterator_new(&current->parent->links);
					while (iterator_has_next(&it))
					{
						t_link	*link = (t_link *)iterator_next(&it);
						if (link->left == current)
							link->mask = LINK_LEFT;
						if (link->right == current)
							link->mask = LINK_RIGHT;
					}
				}
				current = data->end->parent;
			}
			if (!lst_unshift(results, path))
			{
				// TODO free
			}
			int	score = get_score(data->ants, results);
			if (score < *results_score || *results_score == -1)
			{
				*results_score = score;
			}
			else
				break ;
		}
		else
		{
			if (cross)
				cross->mask = LINK_BOTH;
			cross = NULL;
			break ;
		}
	}
}

void	lem_in(t_lem_in *data)
{
	t_list	results;
	int		results_score;
	int		i;

	lst_init(&data->best, (t_consumer)lst_destroy);
	data->best_score = -1;
	data->checks = fmini3(data->ants, data->start->links.size, data->end->links.size);
	while (TRUE)
	{
		i = 0;
		while (i < data->links_len)
		{
			if (data->links[i].mask != LINK_BOTH)
				data->links[i].mask = LINK_NONE;
			i++;
		}
		get_next_path_group(data, &results, &results_score);
		if (results_score != -1 && (results_score < data->best_score || data->best_score == -1))
		{
			lst_clear(&data->best);
			data->best = results;
			data->best_score = results_score;
		}
		else
			break ;
	}
}

int	main(int argc, char const *argv[])
{
	return (0);
}
