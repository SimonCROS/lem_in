/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	reset_links(t_lem_in *data)
{
	int		i;

	i = 0;
	while (i < data->links_len)
	{
		if (data->links[i].mask != LINK_BOTH)
			data->links[i].mask = LINK_NONE;
		i++;
	}
}

char	clear_ret_false(t_list *results)
{
	lst_clear(results);
	return (FALSE);
}

char	get_score(int ants, t_list *paths, int *max)
{
	t_int_tuple	*costs;
	t_iterator	it;
	t_int_tuple	min;
	int			i;

	costs = ft_calloc(paths->size, sizeof(t_int_tuple));
	if (!costs)
		return (FALSE);
	it = iterator_new(paths);
	i = 0;
	while (iterator_has_next(&it))
		costs[i++].l = ((t_list *)iterator_next(&it))->size;
	*max = -1;
	while (ants-- > 0)
	{
		min = costs[0];
		i = 0;
		while (++i < paths->size)
			if (min.l + min.r > costs[i].l + costs[i].r)
				min = costs[i];
		min.r += 1;
		*max = ft_ternary(*max < min.l + min.r, min.l + min.r, *max);
	}
	free(costs);
	return (TRUE);
}
