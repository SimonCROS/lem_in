from __future__ import annotations

class Link:
    left: "Room"
    right: "Room"

    left_valid: bool
    right_valid: bool
    
    def create(left: "Room", right: "Room") -> Link:
        link: Link = Link(left, right)
        left.links.append(link)
        right.links.append(link)
        return link

    def __init__(self, left: "Room", right: "Room") -> None:
        self.left = left
        self.right = right
        self.left_valid = True
        self.right_valid = True

    def is_valid(self) -> bool:
        return self.left_valid or self.right_valid
    
    # -1 for cross -2 for not avaliable
    # c prototype :
    # t_room *tryGetDest(t_link *link, t_room *src, bool *cross)
    def try_get_dest(self, src: "Room") -> "Room" | -1 | -2:
        if self.left == src:
            if not self.right_valid:
                return -2
            if not self.left_valid:
                return -1
            return self.right
        if self.right == src:
            if not self.left_valid:
                return -2
            if not self.right_valid:
                return -1
            return self.left
    
    def invalidate_to(self, dest: "Room"):
        if dest == self.left:
            self.left_valid = False
        if dest == self.right:
            self.right_valid = False
        
    def invalidate(self):
        self.left_valid = False
        self.right_valid = False

    def reset(self):
        self.left_valid = True
        self.right_valid = True