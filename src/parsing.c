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

int	file_opener(char const *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd < 0)
	{
		write(2, "Error opening file\n", 19);
		exit(1);
	}
	return (fd);
}

static void	ant_getter(int fd, t_parser *parsed_data)
{
	char	*line;
	int		i;

	while(ft_get_next_line(fd, 100, &line))
	{
		i = 0;
		while (line[i] && ft_isdigit(line[i]))
			i++;
		if (i == ft_strlen(line) && i != 0)
		{
			parsed_data->ants = ft_atoi(line);
			free(line);
			return ;
		}
		free(line);
	}
	i = 0;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == ft_strlen(line) && i != 0)
	{
		parsed_data->ants = ft_atoi(line);
		free(line);
		return ;
	}
	free(line);
	write(2, "Invalid Map: no ants amount\n", 28);
	exit(1);
}

static void	room_getter(int fd, t_parser *parsed_data)
{

}

static void	link_getter(int fd, t_parser *parsed_data)
{

}

void	parser(int fd)
{
	char		*line;
	t_parser	parsed_data;

	ant_getter(fd, &parsed_data);
	room_getter(fd, &parsed_data);
	link_getter(fd, &parsed_data);

	printf("ants: %i\n", parsed_data.ants);
}
