from __future__ import annotations

class Room:
    name: str
    neighbors: list[Room]

    visited: bool
    selected: bool
    parent: Room | None
    cost: int

    dist: int

    def __init__(self, name: str) -> None:
        self.name = name
        self.neighbors = []

        self.selected = False
        self.visited = False
        self.parent = None
        self.cost = 1
        self.dist = 0

    def __repr__(self) -> str:
        # return f"{self.name} -> {list(n.name for n in self.neighbors)}"
        return f"{self.name}"

    def is_free(self):
        return not self.visited and not self.selected