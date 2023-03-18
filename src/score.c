/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	path_score(t_path *path)
{
	return (path->len + path->ants);
}

int	get_score(int ants, t_list *paths)
{
	int			score;
	t_iterator	it;
	t_path		*path;
	t_path		*min;

	it = iterator_new(paths);
	while (iterator_has_next(&it))
		((t_path *)iterator_next(&it))->ants = 0;
	score = -1;
	min = NULL;
	while (ants-- > 0)
	{
		it = iterator_new(paths);
		while (iterator_has_next(&it))
		{
			path = (t_path *)iterator_next(&it);
			if (!min || path_score(path) < path_score(min))
				min = path;
		}
		min->ants += 1;
		score = fmaxi(path_score(min), score);
	}
	return (score);
}
