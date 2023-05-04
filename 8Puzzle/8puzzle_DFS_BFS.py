from collections import deque

print('Enter initial state: ')

# initial_state = [[int(input()) for _ in range(3)] for _ in range(3)]
initial_state = [[1,2,3],
                [5,6,0],
                [7,8,4]]

print('Enter Goal state: ')
# goal_state = [[int(input()) for _ in range(3)] for _ in range(3)]
goal_state = [[1,2,3],
                [5,8,6],
                [0,7,4]]

def bfs(initial_state,goal_state):
    queue = deque([(initial_state,[])])
    visited = set()

    while queue:
        state, path = queue.popleft()
        if state==goal_state:
            return path + [state]
        if tuple(map(tuple,state)) not in visited:
            visited.add(tuple(map(tuple,state)))
            for move in moves(state):
                new_state = applyMove(state,move)
                new_path = path + [new_state]
                queue.append((new_state,new_path))
    return None

def dfs(initial_state,goal_state):
    stack = [(initial_state,[])]
    visited = set()
    while stack:
        state,path = stack.pop()
        if state==goal_state:
            return path + [state]
        if tuple(map(tuple,state)) not in visited:
            visited.add(tuple(map(tuple,state)))
            for move in moves(state):
                new_state = applyMove(state,move)
                new_path = path + [new_state]
                stack.append((new_state,new_path))

    return None

def applyMove(state,move):
    row,col = find_blank(state)
    new_state = [row[:] for row in state]

    if move=='up':
        new_state[row][col],new_state[row-1][col] = new_state[row-1][col],new_state[row][col]
    elif move=='down':
        new_state[row][col],new_state[row+1][col] = new_state[row+1][col],new_state[row][col]
    elif move=='left':
        new_state[row][col],new_state[row][col-1] = new_state[row][col-1],new_state[row][col]
    elif move=='right':
        new_state[row][col],new_state[row][col+1] = new_state[row][col+1],new_state[row][col]
    
    return new_state

def moves(state):
    move = []
    row,col = find_blank(state)

    if row>0:
        move.append('up')
    if row<2:
        move.append('down')
    if col>0:
        move.append('left')
    if col < 2:
        move.append('right')
    return move

def find_blank(state):
    for i in range(3):
        for j in range(3):
            if state[i][j]==0:
                return i,j

def print_state(state):
    for row in state:
        print(row)
    print()

method = input("Enter method BFS of DFS: ")

if method.lower() == 'bfs':
    solution = bfs(initial_state,goal_state)
elif method.lower() == 'dfs':
    solution = dfs(initial_state,goal_state)
else:
    print("Undefined method")
    solution = None

if solution:
    print('Solution in' , len(solution)-1 , " moves:")
    for state in solution:
        print_state(state)
else:
    print("Solution does not exist.")

