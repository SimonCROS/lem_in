/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	debug_steps(t_lem_in *data)
{
	t_iterator	it;
	t_path		*path;
	int			i;

	get_score(data->ants, &data->best);
	it = iterator_new(&data->best);
	while (iterator_has_next(&it))
	{
		ft_putstr("[");
		path = (t_path *)iterator_next(&it);
		i = 0;
		while (i < path->len)
		{
			ft_putstr(path->rooms[i++]->name);
			if (i < path->len)
				ft_putstr(", ");
		}
		ft_putstr("] -> ");
		ft_putnbr(path->ants);
		ft_putendl(" ants");
	}
	return ;
}
