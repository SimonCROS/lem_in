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

static char	**free_ret_null(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}

static char	*join_free(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}

char	**read_all_lines(int fd)
{
	char	**result;
	char	*content;
	char	*buf;
	ssize_t	rd;

	content = NULL;
	buf = NULL;
	rd = 1;
	while (rd > 0)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (free_ret_null(content, NULL));
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free_ret_null(content, buf));
		buf[rd] = '\0';
		content = join_free(content, buf);
		if (!content)
			return (NULL);
	}
	result = ft_split(content, '\n');
	free(content);
	return (result);
}
