/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clean(t_lem_in *data)
{
	int	i;

	lst_clear(&data->best);
	i = 0;
	while (i < data->rooms_len)
		lst_clear(&data->rooms[i++].links);
	//free(data->rooms);
	//free(data->links);
}

int	main(int argc, char const *argv[])
{
	if (argc != 1)
	{
		write(2, "Wrong number of arguments.", 26);
		write(2, " Usage: ./lem-in\n", 17);
		return (1);
	}
	parser();
    // while(ft_get_next_line(fd, 100, &line))
    // {
    //     write(1, line, ft_strlen(line));
    //     free(line);
    // }
    // write(1, line, ft_strlen(line));
    // free(line);
	return (0);
}
