from __future__ import annotations
import argparse as a

from src.solver import uniform_cost
from src.room import Room
from src.error import Error
from src.parse import parse

ants: int = -1
checks: int = -1
best: list[list[Room]] = None
best_score: int = -1
iteration: int = 0

def _search(current: list[list[Room]], current_score: int, paths: list[list[Room]]):
    global best
    global best_score
    global checks
    global iteration

    for path in paths:
        if not _compatible(path, current):
            continue
        iteration += 1

        if iteration >= checks ** 2:
            break;

        current.append(path)
        new_score = _score(current)
        if new_score < current_score or current_score < 0:
            if new_score < best_score or best_score < 0:
                best = current.copy()
                best_score = new_score
            _search(current, new_score, paths)
        current.remove(path)

def _score(paths: list[list[Room]]) -> int:
    global ants

    i = ants
    paths.sort(key = len)
    costs: list[list[int, int]] = list([len(e), 0] for e in paths)
    max = -1
    while i > 0:
        i -= 1
        lowest = costs[0]
        for c in costs[1:]:
            if lowest[0] + lowest[1] > c[0] + c[1]:
                lowest = c
        lowest[1] += 1
        if max < lowest[0] + lowest[1]:
            max = lowest[0] + lowest[1]
    return max

def _compatible(path: list[Room], paths: list[list[Room]]):
    return not any(_common_data(path[1:-1], c[1:-1]) for c in paths)

def _common_data(list1, list2):
    for x in list1:
        for y in list2:
            if x == y:
                return True
    return False

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
    print(f"Checks: {checks}")

    results: list[list[Room]] = []
    
    i = 0
    while i < (checks ** 2) and (res := uniform_cost(start, end)):
        c = res
        el = []
        while c:
            c.cost += 1
            el.append(c)
            c = c.parent
        
        results.append(el)
        
        # Reset
        for r in rooms.values():
            r.parent = None
        i += 1
    
    print(f"{len(results)} paths found.")
    
    # 1. iterer sur chaque element
    #   LISTE = [element]
    #   2. calculer score -> RES
    #     si RES < best_score
    #       best = LISTE (copie)
    #   3. iterer sur chaque autre element pas dans LISTE -> element2
    #       si element2 compatible score < RES
    #           ajouter element2 à LISTE
    #           rejouer les étapes 2 et 3. (récursion)
    #           retirer element2 de LISTE

    _search([], -1, results)
    print(best)
    print(f"With a score of {_score(best)}")
