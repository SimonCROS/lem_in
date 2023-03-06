from __future__ import annotations
import argparse as a

from src.solver import uniform_cost
from src.room import Room
from src.error import Error
from src.parse import parse

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
    argparse = a.ArgumentParser()
    argparse.add_argument("file", help="file containing the map")

    args = argparse.parse_args()
    (ants, start, end, rooms) = parse(args.file)

    checks = min(ants, len(start.neighbors), len(end.neighbors))
    print(checks)
    
    while res := uniform_cost(start, end):
        print("===== Found =====")
        c = res
        len = 0
        while c:
            print(c.name)
            c.cost += 1
            c = c.parent
            len += 1
        for r in rooms.values():
            r.parent = None
        if end.cost > checks:
            break
    # else:
    #     print("Not found")
