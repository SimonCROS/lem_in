from __future__ import annotations

from room import Room
from link import Link

def _get_path(room: Room):
    path = []
    while room:
        path.append(room)
        room = room.parent
    return path


def bfs(start: Room, goal: Room) -> tuple[list[Room] | None, Link | None]:
    open_list: list[Room] = [start]
    start.selected = True
    first_cross: Link | None = None
    while open_list:
        current: Room = open_list.pop(0)
        if current == goal:
            return (_get_path(current), None)
        for link in current.links:
            child: Room | -1 | -2 = link.try_get_dest(current)
            if child == -1 or child == -2 or child.selected:
                if child == -1:
                    first_cross = link
                continue
            child.selected = True
            child.parent = current
            open_list.append(child)
    return (None, first_cross)
