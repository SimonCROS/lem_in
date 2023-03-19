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

# define BUFFER_SIZE 1000000
# define FAIL 2
# define LINK_NONE 0b00000000
# define LINK_RIGHT 0b00000010
# define LINK_LEFT 0b00000001
# define LINK_BOTH 0b00000011
# define TAG_NONE 0
# define TAG_START 1
# define TAG_END 2

typedef struct s_parser			t_parser;
typedef struct s_lem_in			t_lem_in;
typedef struct s_path			t_path;
typedef struct s_int_tuple		t_int_tuple;
typedef struct s_room			t_room;
typedef struct s_link			t_link;

/*** Structs ******************************************************************/

struct s_lem_in
{
	t_room			*start;
	t_room			*end;
	t_list			rooms;
	t_list			links;
	t_hashmap		rooms_names;
	t_list			best;
	char			**lines;
	int				best_score;
	int				checks;
	int				ants;
};

// The rooms array is stored just after this struct
struct s_path
{
	int				len;
	int				ants;
	t_room			**rooms;
};

struct s_room
{
	t_centry		entry_open_bfs;
	char			*name;
	t_list			links;
	t_room			*parent;
	int				x;
	int				y;
	int				ant;
	int				dist;
	int				used;
};

struct s_link
{
	t_room			*left;
	t_room			*right;
	char			mask;
};

/*** Algo *********************************************************************/

char	lem_in(t_lem_in *data);

/*** BFS **********************************************************************/

char	bfs(t_room *start, t_room *goal, t_link **cross);

/*** Parsing ******************************************************************/

char	**read_all_lines(int fd);
char	parser(t_lem_in *data);

/*** Score *******************************************************************/

int		get_score(int ants, t_list *paths);
void	print_result(t_lem_in *data);

/*** Utils ********************************************************************/

char	create_link(t_room *left, t_room *right, t_link **link);
char	create_room(char *name, int x, int y, t_room **room);
void	reset_datas(t_lem_in *data);
char	clear_ret_false(t_list *results);
void	disable_link(t_room *from, t_room *to);

/*** Debug ********************************************************************/

void	debug_steps(t_lem_in *data);

#endif
