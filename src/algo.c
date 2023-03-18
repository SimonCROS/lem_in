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
	if (!path || !lst_unshift(results, path))
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
		else
			return (2);
	}
	if (cross)
		cross->mask = LINK_BOTH;
	return (2);
}

static char	get_path_group(t_lem_in *data, t_list *results, int *results_score)
{
	int		i;
	char	res;

	lst_init(results, (t_consumer)free);
	*results_score = -1;
	while (TRUE)
	{
		if (results->size >= data->checks)
			break ;
		i = 0;
		while (i < data->rooms_len)
		{
			data->rooms[i].dist = 0;
			data->rooms[i].parent = NULL;
			i++;
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
	int		results_score;

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
