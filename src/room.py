from __future__ import annotations

class Room:
    name: str
    neighbors: list[Room]

    visited: bool
    selected: bool
    parent: Room | None
    cost: int

    def __init__(self, name: str) -> None:
        self.name = name
        self.neighbors = []

        self.selected = False
        self.visited = False
        self.parent = None
        self.cost = 1

    def __repr__(self) -> str:
        return f"{self.name} -> {list(n.name for n in self.neighbors)}"

    def is_free(self):
        return not self.visited and not self.selected
    
    def visit_neighbor(self):
        for n in neighbors:
            pass