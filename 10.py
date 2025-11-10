import heapq

FREE = 0
OBSTACLE = 1
START = 'S'
GOAL = 'G'
PATH = '*'

class Node:
    def __init__(self, position, parent=None, g=0, h=0):
        self.position = position
        self.parent = parent
        self.g = g
        self.h = h
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

def astar_search(maze, start, goal):
    open_list = []
    closed_set = set()
    start_node = Node(start, None, 0, heuristic(start, goal))
    heapq.heappush(open_list, start_node)

    while open_list:
        current_node = heapq.heappop(open_list)
        closed_set.add(current_node.position)

        if current_node.position == goal:
            path = []
            node = current_node
            while node:
                path.append(node.position)
                node = node.parent
            return path[::-1]

        for move in [(0,1),(1,0),(0,-1),(-1,0)]:
            neighbor_pos = (current_node.position[0] + move[0],
                            current_node.position[1] + move[1])
            r, c = neighbor_pos
            if 0 <= r < len(maze) and 0 <= c < len(maze[0]) and maze[r][c] != OBSTACLE:
                if neighbor_pos in closed_set:
                    continue
                g_cost = current_node.g + 1
                h_cost = heuristic(neighbor_pos, goal)
                neighbor_node = Node(neighbor_pos, current_node, g_cost, h_cost)
                heapq.heappush(open_list, neighbor_node)
    return None

def print_maze(maze, path=None, start=None, goal=None):
    maze_copy = [row[:] for row in maze]
    if path:
        for r, c in path:
            if (r, c) != start and (r, c) != goal:
                maze_copy[r][c] = PATH
    if start:
        maze_copy[start[0]][start[1]] = START
    if goal:
        maze_copy[goal[0]][goal[1]] = GOAL
    for row in maze_copy:
        print(' '.join(str(cell) for cell in row))
    print()

if __name__ == "__main__":
    maze = [
        [0, 0, 0, 0, 1],
        [1, 1, 0, 1, 0],
        [0, 0, 0, 0, 0],
        [0, 1, 1, 1, 0],
        [0, 0, 0, 0, 0]
    ]
    start = (0, 0)
    goal = (4, 4)
    print("Maze:")
    print_maze(maze, start=start, goal=goal)
    path = astar_search(maze, start, goal)
    if path:
        print("Optimal Path Found:")
        print_maze(maze, path, start, goal)
        print("Path sequence:", path)
    else:
        print("No path found!")
