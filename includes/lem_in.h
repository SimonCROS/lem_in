#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/*** Types ********************************************************************/

# define FAIL 2

typedef struct s_room			t_room;
typedef struct s_link			t_link;

/*** Structs ******************************************************************/

struct s_room
{
	t_centry		entry_best;
	t_centry		entry_results;
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
	char			left_valid;
	char			right_valid;
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
