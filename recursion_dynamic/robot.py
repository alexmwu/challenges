#!/usr/bin/env python

grid = [[1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1]]
grid0 = [[1, 0, 1, 1, 1],
        [1, 0, 1, 1, 0],
        [1, 1, 1, 1, 1],
        [0, 1, 1, 1, 0],
        [1, 1, 0, 1, 1]]
grid1 = [[0, 1 ,1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 0]]
grid2 = [[1, 1, 1],
        [1, 1, 0],
        [1, 0, 1]]
grid3 = []
grid4 = [[]]

def findGridPath(grid):
    if not checkGrid(grid):
        return False
    path = []
    if not findPath(path, grid, 0, 0):
        return False
    return path

def findPath(path, grid, row, col):
    if row >= len(grid) or col >= len(grid[0]) or grid[row][col] == 0:
        return False
    if isDone(row, col, grid) or findPath(path, grid, row + 1, col) or findPath(path, grid, row, col + 1):
        path.append([row, col])
        return True
    return False

def checkGrid(grid):
    if len(grid) == 0:
        return False
    elif len(grid[0]) == 0:
        return False
    elif grid[0][0] == 0:
        return False
    return True

def isDone(row, col, grid):
    if row == len(grid) - 1 and col == len(grid[0]) - 1:
        return True
    return False

def isWalkable(grid, r, c):
    if r >= len(grid):
        return False
    elif c >= len(grid[0]):
        return False
    elif grid[r][c] == 0:
        return False
    else:
        return True

def initPath(path):
    if len(path) == 0:
        path.append([0, 0])

print findGridPath(grid)
print findGridPath(grid0)
print findGridPath(grid1)
print findGridPath(grid2)
print findGridPath(grid3)
print findGridPath(grid4)

