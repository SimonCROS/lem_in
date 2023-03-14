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

#endif
