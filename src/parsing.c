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

static char	parse_room(t_lem_in *da, char *li, char next_tag)
{
	t_room	*room;
	int		s1;
	int		s2;
	int		x;
	int		y;

	s1 = ft_strindex_of(li, ' ');
	s2 = ft_strindex_of(li + s1 + 1, ' ') + s1 + 1;
	li[s1] = '\0';
	li[s2] = '\0';
	if (!ft_strlen(li) || !ft_strlen(li + s1 + 1) || !ft_strlen(li + s2 + 1)
		|| !ft_atoi_full(li + s1 + 1, &x) || !ft_atoi_full(li + s2 + 1, &y))
		return (next_tag == TAG_NONE);
	room = NULL;
	if (!create_room(li, (int)x, (int)y, &room) || !lst_push(&da->rooms, room)
		|| !hashmap_set(&da->rooms_names, room->name, room))
	{
		free(room);
		return (FALSE);
	}
	if (next_tag == TAG_START)
		da->start = room;
	if (next_tag == TAG_END)
		da->end = room;
	return (2);
}

static char	room_getter(t_lem_in *data, char **lines, int *i)
{
	int		ret;
	char	*line;
	char	next_tag;

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
		if (ft_strcnt(line, ' ') != 2 || ft_starts_with(line, "L"))
			return (next_tag == TAG_NONE);
		ret = parse_room(data, lines[(*i)++], next_tag);
		if (ret != 2)
			return (ret);
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
