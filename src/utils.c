#include "lem_in.h"

void	*room_to_best_entry(t_room *room)
{
	return ((void *)room + 0);
}

void	*room_to_results_entry(t_room *room)
{
	return ((void *)room + 8);
}

void	*room_to_bfs_open_entry(t_room *room)
{
	return ((void *)room + 16);
}

t_room	*best_entry_to_room(void *entry)
{
	return ((t_room *)entry - 0);
}

t_room	*results_entry_to_room(void *entry)
{
	return ((t_room *)entry - 8);
}

t_room	*bfs_open_entry_to_room(void *entry)
{
	return ((t_room *)entry - 16);
}
