from __future__ import annotations

from src.link import Link

class Room:
    name: str
    links: list["Link"]

    selected: bool
    parent: Room | None

    dist: int

    def __init__(self, name: str) -> None:
        self.name = name
        self.neighbors = []
        self.links = []

        self.selected = False
        self.parent = None
        self.cost = 1
        self.dist = 0

    def __repr__(self) -> str:
        return f"{self.name}"
