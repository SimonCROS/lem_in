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

static char	append_path(t_list *results, t_room *last)
{
	t_path	*path;
	int		i;

	path = malloc(sizeof(t_path) + (sizeof(t_room *) * (last->dist + 1)));
	if (!path || !lst_push(results, path))
	{
		free(path);
		return (FALSE);
	}
	path->len = last->dist + 1;
	path->ants = 0;
	path->rooms = ((void *)path) + sizeof(t_path);
	i = 0;
	while (last)
	{
		last->used = TRUE;
		path->rooms[path->len - i - 1] = last;
		disable_link(last->parent, last);
		last = last->parent;
		i++;
	}
	return (TRUE);
}

static char	get_next_path(t_lem_in *data, t_list *results, int *results_score)
{
	t_link	*cross;
	int		score;

	if (bfs(data->start, data->end, &cross))
	{
		if (!append_path(results, data->end))
			return (clear_ret_false(results));
		score = get_score(data->ants, results);
		if (score < *results_score || *results_score == -1)
		{
			*results_score = score;
			return (1);
		}
	}
	if (cross)
		cross->mask = LINK_BOTH;
	return (2);
}

static char	get_path_group(t_lem_in *data, t_list *results, int *results_score)
{
	t_iterator	it;
	t_room		*room;
	char		res;

	lst_init(results, (t_consumer)free);
	*results_score = -1;
	it = iterator_new(&data->rooms);
	while (iterator_has_next(&it))
	{
		room = (t_room *)iterator_next(&it);
		room->used = FALSE;
	}
	while (TRUE)
	{
		if (results->size >= data->checks)
			break ;
		it = iterator_new(&data->rooms);
		while (iterator_has_next(&it))
		{
			room = (t_room *)iterator_next(&it);
			room->dist = 0;
			room->parent = NULL;
		}
		res = get_next_path(data, results, results_score);
		if (res == FALSE)
			return (FALSE);
		if (res == 2)
			break ;
	}
	return (TRUE);
}

char	lem_in(t_lem_in *data)
{
	t_list	results;
	int		rs;

	data->checks = fmini3(data->ants,
			data->start->links.size, data->end->links.size);
	while (TRUE)
	{
		reset_links(data);
		if (!get_path_group(data, &results, &rs))
			return (clear_ret_false(&data->best));
		if (rs != -1 && (rs < data->best_score || data->best_score == -1))
		{
			lst_clear(&data->best);
			if (!lst_copy_to(&results, &data->best))
				return (clear_ret_false(&results));
			lst_shallow_clear(&results);
			data->best_score = rs;
		}
		else
		{
			lst_clear(&results);
			break ;
		}
	}
	return (TRUE);
}
