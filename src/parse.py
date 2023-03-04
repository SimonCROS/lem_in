
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

if __name__ == '__main__':
    room_pattern = re.compile(r"^([^-]+) \d+ \d+$")
    link_pattern = re.compile(r"^([^-]+)-([^-]+)$")

    argparse = a.ArgumentParser()
    argparse.add_argument("file", help="file containing the map")

    args = argparse.parse_args()
    lines = __get_file_content(args.file)

    ants: int = -1
    start: Room = None
    end: Room = None
    rooms: dict[str, Room] = {}
    rooms_finished: bool = False

    lines = list(__remove_comment(line) for line in lines)
    for i in range(0, len(lines)):
        line = lines[i]
        if not line:
            continue
        if ants == -1:
            if not line.isdigit():
                raise Error()
            ants = int(line)
            continue
        if not rooms_finished:
            if line == "##start":
                i += 1
                line = lines[i]
                if result := re.search(room_pattern, line):
                    start = Room(result.group(1))
                    rooms[result.group(1)] = start
            elif line == "##end":
                i += 1
                line = lines[i]
                if result := re.search(room_pattern, line):
                    end = Room(result.group(1))
                    rooms[result.group(1)] = end
            elif result := re.search(room_pattern, line):
                rooms[result.group(1)] = Room(result.group(1))
            else:
                rooms_finished = True
        if rooms_finished:
            if result := re.search(link_pattern, line):
                room1: Room = rooms[result.group(1)]
                room2: Room = rooms[result.group(2)]
                room1.neighbors.append(room2)
                room2.neighbors.append(room1)
    print(f"Ants: {ants}\nGoal: {start.name} -> {end.name}\n{rooms}")
