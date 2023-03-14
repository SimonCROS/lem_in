from __future__ import annotations

import heapq

from src.room import Room
from src.link import Link

def _get_path(room: Room):
    path = []
    while room:
        room.visited = True
        path.append(room)
        room = room.parent
    
    return path


def bfs(start: Room, goal: Room, max_len: int) -> tuple[list[Room] | None, Link | None]:
    open_list: list[Room] = [start]
    
    start.selected = True

    first_cross: Link | None = None
    while open_list:
        current: Room = open_list.pop(0)

        if current.dist > max_len and max_len != -1:
            return None

        if current == goal:
            return (_get_path(current), None)

        for link in current.links:
            child: Room | -1 | -2 = link.try_borrow_dest(current)
            if child == -1 or child == -2:
                if child == -1 and not first_cross:
                    first_cross = link
                continue
                
            if child.selected:
                continue

            child.dist = current.dist + 1
            child.selected = True
            child.parent = current

            open_list.append(child)
    
    return (None, first_cross)
