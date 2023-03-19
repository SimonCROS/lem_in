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
	int		space1;
	int		space2;
	int		x;
	int		y;
	t_room	*room;

	next_tag = TAG_NONE;
	while (lines[*i])
	{
		line = lines[*i];
		if (ft_starts_with(line, "#"))
		{
			(*i)++;
			if (ft_strcmp(line, "##start") == 0)
				next_tag = TAG_START;
			if (ft_strcmp(line, "##end") == 0)
				next_tag = TAG_END;
			continue ;
		}
		if (ft_strcnt(line, ' ') != 2)
			return (next_tag == TAG_NONE);
		(*i)++;
		space1 = ft_strindex_of(line, ' ');
		space2 = ft_strindex_of(line + space1 + 1, ' ') + space1 + 1;
		line[space1] = '\0';
		line[space2] = '\0';
		if (!ft_strlen(line) || !ft_strlen(line + space1 + 1)
			|| !ft_strlen(line + space2 + 1)
			|| !ft_atoi_full(line + space1 + 1, &x)
			|| !ft_atoi_full(line + space2 + 1, &y))
			return (next_tag == TAG_NONE);
		room = NULL;
		if (!create_room(line, (int)x, (int)y, &room)
			|| !lst_push(&data->rooms, room)
			|| !hashmap_set(&data->rooms_names, room->name, room))
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
	char	*line;
	t_room	*left;
	t_room	*right;
	t_link	*link;
	int		separator;

	while (lines[*i])
	{
		line = lines[*i];
		(*i)++;
		if (ft_starts_with(line, "#"))
			continue ;
		separator = ft_strindex_of(line, '-');
		if (separator == -1)
			return (FALSE);
		line[separator] = '\0';
		left = hashmap_get(&data->rooms_names, line);
		right = hashmap_get(&data->rooms_names, line + separator + 1);
		if (!left || !right
			|| !create_link(left, right, &link)
			|| !lst_push(&data->links, link))
			return (FALSE);
	}
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
