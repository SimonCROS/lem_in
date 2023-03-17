/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_rooms(t_lem_in *data)
{
	int		i;
	t_room	*room;

	i = 0;
	while (i < data->rooms_len)
	{
		room = data->rooms + i;
		if (room == data->start)
			ft_putendl("##start");
		if (room == data->end)
			ft_putendl("##end");
		ft_putstr(room->name);
		ft_putstr(" ");
		ft_putnbr(room->x);
		ft_putstr(" ");
		ft_putnbr(room->y);
		ft_putendl("");
		i++;
	}
}

static void	print_links(t_lem_in *data)
{
	int		i;
	t_link	*link;

	i = 0;
	while (i < data->links_len)
	{
		link = data->links + i;
		ft_putstr(link->left->name);
		ft_putstr("-");
		ft_putendl(link->right->name);
		i++;
	}
}

static void	print_path_step(t_path *path,
		int *finished, char *first_of_line, int *next_ant)
{
	int	i;
	int	ant;

	i = path->len;
	while (i-- > 1)
	{
		ant = path->rooms[i - 1]->ant;
		if (i == 1 && path->ants-- > 0)
			ant = (*next_ant)++;
		if (ant == 0)
			continue ;
		path->rooms[i]->ant = ant;
		if (!*first_of_line)
			ft_putstr(" ");
		ft_putstr("L");
		ft_putnbr(path->rooms[i]->ant);
		ft_putstr("-");
		ft_putstr(path->rooms[i]->name);
		*first_of_line = FALSE;
		path->rooms[i - 1]->ant = 0;
		if (i == path->len - 1)
			(*finished)++;
	}
}

static void	print_steps(t_lem_in *data)
{
	t_iterator	it;
	int			finished;
	int			next_ant;
	char		first_of_line;

	get_score(data->ants, &data->best);
	finished = 0;
	next_ant = 1;
	while (finished < data->ants)
	{
		first_of_line = TRUE;
		it = iterator_new(&data->best);
		while (iterator_has_next(&it))
			print_path_step((t_path *)iterator_next(&it),
				&finished, &first_of_line, &next_ant);
		ft_putendl("");
	}
	return ;
}

void	print_result(t_lem_in *data)
{
	ft_putnbr(data->ants);
	ft_putendl("");
	print_rooms(data);
	print_links(data);
	ft_putendl("");
	print_steps(data);
}
