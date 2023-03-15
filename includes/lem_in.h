/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:00:00 by scros             #+#    #+#             */
/*   Updated: 2023/03/15 00:00:00 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*** Types ********************************************************************/

# define FAIL 2
# define LINK_NONE 0b00000000
# define LINK_RIGHT 0b00000010
# define LINK_LEFT 0b00000001
# define LINK_BOTH 0b00000011

typedef struct s_lem_in			t_lem_in;
typedef struct s_int_tuple		t_int_tuple;
typedef struct s_room			t_room;
typedef struct s_link			t_link;

/*** Structs ******************************************************************/

struct s_lem_in
{
	t_room			*start;
	t_room			*end;
	t_room			*rooms;
	t_link			*links;
	t_list			best;
	int				best_score;
	int				checks;
	int				ants;
	int				rooms_len;
	int				links_len;
};

struct s_int_tuple
{
	int				l;
	int				r;
};

struct s_room
{
	t_centry		entry_open_bfs;
	char			*name;
	t_list			links;
	t_room			*parent;
	char			selected;
};

struct s_link
{
	t_room			*left;
	t_room			*right;
	char			mask;
};

/*** BFS **********************************************************************/

char		bfs(t_room *start, t_room *goal, t_link **cross);

/*** Parsing ******************************************************************/

int 		ft_get_next_line(int fd, int b_size, char **line);

/*** Utils ********************************************************************/

#endif
