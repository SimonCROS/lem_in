from __future__ import annotations

import heapq

from src.room import Room


def uniform_cost(start: Room, goal: Room) -> Room | None:
    open_list_q: list[tuple[float, str]] = [(start.cost, start.name)]
    open_list: dict[str, Room] = {start.name: start}
    closed_list: dict[str, Room] = {}

    while open_list:
        current_q = heapq.heappop(open_list_q)

        while closed_list.get(current_q[1]):
            current_q = heapq.heappop(open_list_q)

        current: Room = open_list[current_q[1]]

        closed_list[current.name] = current
        del open_list[current.name]

        if current == goal:
            return current

        for child in current.neighbors:
            if child.visited or closed_list.get(child.name):
                continue

            if open_list.get(child.name) is None or child.cost < open_list[child.name].cost:
                heapq.heappush(open_list_q, (child.cost, child.name))
                open_list[child.name] = child
                child.parent = current
    
    return None
