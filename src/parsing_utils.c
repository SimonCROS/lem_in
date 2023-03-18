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

char	**read_all_lines(int fd)
{
	char	**result;
	char	*content;
	char	*tmp;
	char	*buf;
	ssize_t	rd;

	content = NULL;
	buf = NULL;
	tmp = NULL;
	rd = 1;
	while (rd > 0)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
		{
			free(content);
			return (NULL);
		}
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
		{
			free(content);
			free(buf);
			return (NULL);
		}
		buf[rd] = '\0';
		tmp = content;
		content = ft_strjoin(tmp, buf);
		free(tmp);
		free(buf);
		if (!content)
			return (NULL);
	}
	result = ft_split(content, '\n');
	free(content);
	return (result);
}
