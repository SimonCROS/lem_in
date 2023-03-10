from __future__ import annotations
import argparse as a

from src.solver import uniform_cost
from src.room import Room
from src.parse import parse
import math

ants: int = -1
best: list[list[Room]] = None
best_score: int = -1

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

if __name__ == '__main__':
    argparse = a.ArgumentParser()
    argparse.add_argument("file", help="file containing the map")

    args = argparse.parse_args()
    (ants, start, end, rooms) = parse(args.file)

    checks = min(ants, len(start.neighbors), len(end.neighbors))
    print(f"Checks: {checks}")

    previous_score = -1
    results: list[list[Room]] = []
    
    i = 0
    iter = (checks ** 2)
    while i < iter:
        start.cost = 0
        end.cost = 0
        start.visited = False
        end.visited = False

        if i % 1000 == 0:
            print(f"{best_score} ({math.ceil(i * 100 / iter)}%)")
        res = uniform_cost(start, end, best_score)
        if res:
            el = []
            c = res
            while c:
                c.visited = True
                el.append(c)
                c = c.parent

            if len(el) < best_score or best_score == -1:
                results.append(el)

                score = _score(results)
                print(score, len(results), len(el))
                if score < previous_score or previous_score == -1:
                    previous_score = score
                    if score < best_score or best_score == -1:
                        best = results.copy()
                        best_score = score
                else:
                    res = None
            else:
                res = None

        for r in rooms.values():
            r.parent = None
        
        if not res:
            for e in results:
                for r in e:
                    r.cost += 1

            # Reset
            for r in rooms.values():
                r.visited = False
            results = []
            previous_score = -1

        i += 1
    
    print(best)
    if best:
        print(f"With a score of {_score(best) - 2}")
