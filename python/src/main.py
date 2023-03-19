from __future__ import annotations
import argparse as a

from bfs import bfs
from room import Room
from parse import parse

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
    (ants, start, end, rooms, links) = parse(args.file)

    checks = min(ants, len(start.links), len(end.links))

    while True:
        results: list[list[Room]] = []
        results_score = -1
        
        # Clean before
        for l in links:
            if l.is_valid():
                l.reset()
        
        while True:
            if len(results) >= checks:
                break
            
            # Clean before
            for r in rooms.values():
                r.selected = False

            (path, cross) = bfs(end, start)

            if not path:
                if cross:
                    cross.invalidate()
                break
            
            for step in path:
                if step.parent:
                    for link in step.parent.links:
                        link.invalidate_to(step)
            
            results.append(path)
            score = _score(results)
            if score < results_score or results_score == -1:
                results_score = score
            else:
                break
        
        if results_score == -1:
            break

        if results_score < best_score or best_score == -1:
            best = results.copy()
            best_score = results_score
        else:
            break

    for a in best:
        print(a);
    if best:
        print(f"With a score of {_score(best) - 2}")
