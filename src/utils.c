#include "lem_in.h"

void	*room_to_bfs_open_entry(t_room *room)
{
	return ((void *)room + 0);
}

t_room	*bfs_open_entry_to_room(void *entry)
{
	return ((t_room *)entry - 0);
}
