from __future__ import annotations

from src.link import Link

class Room:
    name: str
    links: list["Link"]

    selected: bool
    parent: Room | None

    def __init__(self, name: str) -> None:
        self.name = name
        self.links = []

        self.selected = False
        self.parent = None

    def __repr__(self) -> str:
        return f"{self.name}"
