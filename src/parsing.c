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

// can't open files
// int	file_opener(char const *path)
// {
// 	int	fd;

// 	fd = open(path, O_RDWR);
// 	if (fd < 0)
// 	{
// 		write(2, "Error opening file\n", 19);
// 		exit(1);
// 	}
// 	return (fd);
// }

static void	ant_getter(t_lem_in *parsed_data)
{
	char	*line;

	parsed_data->ants = -1;
	while(ft_get_next_line(0, 100, &line))
	{
		parsed_data->ants = ant_checker(line);
		if (parsed_data->ants >= 0)
			return ;
	}
	parsed_data->ants = ant_checker(line);
	if (parsed_data->ants >= 0)
		return ;
	write(2, "Invalid Map: no ants amount\n", 28);
	exit(1);
}

static void	room_getter(t_lem_in *parsed_data)
{

}

static void	link_getter(t_lem_in *parsed_data)
{

}

t_lem_in	parser(void)
{
	t_lem_in	parsed_data;

	ant_getter(&parsed_data);
	room_getter(&parsed_data);
	link_getter(&parsed_data);

	printf("ants: %i\n", parsed_data.ants);
	return (parsed_data);
}
