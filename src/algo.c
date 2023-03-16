/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	disable_link_to(t_room *room)
{
	t_iterator	it;
	t_link		*link;

	if (room->parent)
	{
		it = iterator_new(&room->parent->links);
		while (iterator_has_next(&it))
		{
			link = (t_link *)iterator_next(&it);
			if (link->left == room)
				link->mask = LINK_LEFT;
			if (link->right == room)
				link->mask = LINK_RIGHT;
		}
	}
}

static t_list	*build_path_from_parents(t_room *last)
{
	t_list		*path;
	t_room		*current;

	path = lst_new(NULL);
	if (!path)
		return (NULL);
	current = last;
	while (current)
	{
		if (!lst_unshift(path, current))
		{
			lst_destroy(path);
			return (NULL);
		}
		disable_link_to(current);
		current = current->parent;
	}
	return (path);
}

static char	get_path_group(t_lem_in *data, t_list *results, int *results_score)
{
	t_link		*cross;
	t_list		*path;
	int			i;
	int			score;

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
			data->rooms[i].parent = NULL;
			i++;
		}
		if (bfs(data->start, data->end, &cross))
		{
			path = build_path_from_parents(data->end);
			if (!path || !lst_unshift(results, path)
				|| !get_score(data->ants, results, &score))
			{
				lst_destroy(path);
				lst_clear(results);
				return (FALSE);
			}
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
	return (TRUE);
}

char	lem_in(t_lem_in *data)
{
	t_list	results;
	int		results_score;

	lst_init(&data->best, (t_consumer)lst_destroy);
	data->best_score = -1;
	data->checks = fmini3(data->ants,
			data->start->links.size, data->end->links.size);
	while (TRUE)
	{
		reset_links(data);
		if (!get_path_group(data, &results, &results_score))
			return (clear_ret_false(&data->best));
		if (results_score != -1
			&& (results_score < data->best_score || data->best_score == -1))
		{
			lst_clear(&data->best);
			if (!lst_copy_to(&results, &data->best))
				return (clear_ret_false(&results));
			lst_shallow_clear(&results);
			data->best_score = results_score;
		}
		else
		{
			lst_clear(&results);
			break ;
		}
	}
	return (TRUE);
}
