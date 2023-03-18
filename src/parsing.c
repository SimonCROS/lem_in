/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctaleb <ctaleb@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by ctaleb            #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by ctaleb           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	ant_getter(t_lem_in *data, char **lines, int *i)
{
	char	*line;

	data->ants = -1;
	while (lines[*i])
	{
		line = lines[*i];
		(*i)++;
		if (ft_starts_with(line, "#"))
			continue ;
		if (!ft_atoi_full(line, &data->ants))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static char	room_getter(t_lem_in *data, char **lines, int *i)
{
	char	*line;
	char	next_tag;

	while (lines[*i])
	{
		line = lines[*i];
		(*i)++;
		if (ft_starts_with(line, "#"))
		{
			if (ft_strcmp(line, "##start"))
				next_tag = TAG_START;
			if (ft_strcmp(line, "##end"))
				next_tag = TAG_END;
			continue ;
		}
		if (ft_strcnt(line, ' ') != 2)
			return (TRUE);
		int		space1 = ft_strindex_of(line, ' ');
		int		space2 = ft_strindex_of(line + space1 + 1, ' ') + space1 + 1;
		int		x;
		int		y;

		line[space1] = '\0';
		line[space2] = '\0';
		if (!ft_strlen(line) || !ft_strlen(line + space1 + 1)
			|| !ft_strlen(line + space2 + 1) 
			|| !ft_atoi_full(line + space1 + 1, &x)
			|| !ft_atoi_full(line + space2 + 1, &y))
			return (next_tag == TAG_NONE);
		
		t_room	*room;
		
		room = NULL;
		if (!create_room(line, (int)x, (int)y, &room)
			|| !lst_unshift(&data->rooms, room))
		{
			free(room);
			return (FALSE);
		}
		if (next_tag == TAG_START)
			data->start = room;
		if (next_tag == TAG_END)
			data->end = room;
		next_tag = TAG_NONE;
	}
	return (FALSE);
}

static char	link_getter(t_lem_in *data, char **lines, int *i)
{
	(void)data;
	(void)lines;
	(void)i;
	return (TRUE);
}

char	parser(t_lem_in *data)
{
	int		line;

	line = 0;
	data->lines = read_all_lines(0);
	if (!data->lines
		|| !ant_getter(data, data->lines, &line) || data->ants < 1
		|| !room_getter(data, data->lines, &line) || !data->start || !data->end
		|| !link_getter(data, data->lines, &line))
		return (FALSE);
	return (TRUE);
}
