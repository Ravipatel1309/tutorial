from collections import deque

graph = {
    'A':['B','C','E'],
    'B': ['E', 'F'],
    'C': ['D'],
    'D': ['F'],
    'E': ['C'],
    'F': ['D']
}

def bfs(graph,start,end):
    queue = deque([(start,[start])])
    while queue:
        node, path = queue.popleft()
        for neighbour in graph[node]:
            if neighbour not in path:
                if neighbour==end:
                    return path+ [neighbour]
                else:
                    queue.append((neighbour,path+[neighbour]))
    return None

            
start = input("Start node: ")
end = input("End node: ")

path = bfs(graph,start,end)

if path is None:
    print("Not exist.")
else:
    print(path)