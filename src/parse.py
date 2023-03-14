from __future__ import annotations
import re

from src.room import Room
from src.link import Link
from src.error import Error

def __get_file_content(file: str) -> list[str]:
    lines: list[str] = []

    try:
        f = open(file, 'r')
        lines = f.readlines()
    except FileNotFoundError:
        Error.throw(Error.FAIL, Error.FILE_NOT_FOUND_ERROR,
                    f"no such file: {file}")
    except IsADirectoryError:
        Error.throw(Error.FAIL, Error.IS_A_DIRECTORY_ERROR,
                    f"is a directory: {file}")
    except PermissionError:
        Error.throw(Error.FAIL, Error.PERMISSION_ERROR,
                    f"permission denied: {file}")
    except UnicodeDecodeError:
        Error.throw(Error.FAIL, Error.UNICODE_DECODE_ERROR,
                    f"'utf-8' codec can't decode byte: {file}")
    return lines

def __remove_comment(line: str) -> str:
    line = line.removesuffix("\n").strip()
    if line == '##start' or line == "##end":
        return line
    
    comment_index = line.find('#')
    if comment_index != -1:
        return line[:comment_index].strip()
    return line

def parse(file: str) -> tuple[int, Room, Room, dict[str, Room], list[Link]]:
    room_pattern = re.compile(r"^([^-]+) \d+ \d+$")
    link_pattern = re.compile(r"^([^-]+)-([^-]+)$")

    lines = __get_file_content(file)

    ants: int = -1
    start: Room = None
    end: Room = None
    rooms: dict[str, Room] = {}
    rooms_finished: bool = False
    links: list[Link] = []

    lines = list(__remove_comment(line) for line in lines)
    i = 0
    l = len(lines)
    while i < l:
        line = lines[i]
        i += 1
        if not line:
            continue
        if ants == -1:
            if not line.isdigit():
                raise Error()
            ants = int(line)
            continue
        if not rooms_finished:
            if line == "##start":
                line = lines[i]
                i += 1
                if result := re.search(room_pattern, line):
                    start = Room(result.group(1))
                    rooms[start.name] = start
            elif line == "##end":
                line = lines[i]
                i += 1
                if result := re.search(room_pattern, line):
                    end = Room(result.group(1))
                    rooms[end.name] = end
            elif result := re.search(room_pattern, line):
                room = Room(result.group(1))
                rooms[room.name] = room
            else:
                rooms_finished = True
        if rooms_finished:
            if result := re.search(link_pattern, line):
                links.append(Link.create(rooms[result.group(1)], rooms[result.group(2)]))
    # print(f"Ants: {ants}\nGoal: {start.name} -> {end.name}\n{rooms}")

    return (ants, start, end, rooms, links)
