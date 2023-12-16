grid = []
n = m = 0
def readlines():
    with open("day11/input.txt", "r") as f:
        l = f.readlines();
    return l

def expand_universe(grid):
    row = [False]*len(grid)
    col = [False]*len(grid[0])
    for i in range(len(grid)):
        for j in range(len(grid[i])):
            if (grid[i][j] == '#'):
                row[i], col[j] = True, True;

    d = 0
    for i in range(len(grid)):
        if row[i]:
            grid.insert(i+d, '.' * len(grid[0]) )
            d += 1
            
    for i in range(len(grid)): print(grid[i], end='')
    print()
    
    for j in range(len(grid[0])):
        if col[j]:
            for i in range(len(grid)):
                grid[i].insert(j, '.')


    return grid

grid = expand_universe(readlines())
# for i in range(n):
#     print(grid[i])