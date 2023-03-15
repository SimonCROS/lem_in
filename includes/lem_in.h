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

/*** Types ********************************************************************/

# define FAIL 2
# define LINK_NONE 0b00000000
# define LINK_RIGHT 0b00000010
# define LINK_LEFT 0b00000001
# define LINK_BOTH 0b00000011

typedef struct s_room			t_room;
typedef struct s_link			t_link;

/*** Structs ******************************************************************/

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

/*** Utils ********************************************************************/

void		*room_to_best_entry(t_room *room);
void		*room_to_results_entry(t_room *room);
void		*room_to_bfs_open_entry(t_room *room);
t_room		*best_entry_to_room(void *entry);
t_room		*results_entry_to_room(void *entry);
t_room		*bfs_open_entry_to_room(void *entry);

#endif
