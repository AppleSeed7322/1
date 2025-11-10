import networkx as nx
import matplotlib.pyplot as plt

departments = ['CS', 'EE', 'ME', 'CE']
edges = [
    ('CS', 'EE', 4),
    ('CS', 'ME', 6),
    ('CS', 'CE', 8),
    ('EE', 'ME', 3),
    ('EE', 'CE', 5),
    ('ME', 'CE', 7)
]

index = {dept: i for i, dept in enumerate(departments)}
n = len(departments)

adj_list = {dept: [] for dept in departments}
for src, dest, dist in edges:
    adj_list[src].append((dest, dist))
    adj_list[dest].append((src, dist))

print("Adjacency List:")
for k, v in adj_list.items():
    print(f"{k}: {v}")

adj_matrix = [[0] * n for _ in range(n)]
for src, dest, dist in edges:
    i, j = index[src], index[dest]
    adj_matrix[i][j] = dist
    adj_matrix[j][i] = dist

print("\nAdjacency Matrix:")
for row in adj_matrix:
    print(row)

def kruskal(departments, edges):
    parent = {dept: dept for dept in departments}

    def find(u):
        while parent[u] != u:
            parent[u] = parent[parent[u]]
            u = parent[u]
        return u

    def union(u, v):
        parent[find(u)] = find(v)

    mst = []
    edges_sorted = sorted(edges, key=lambda x: x[2])
    for u, v, w in edges_sorted:
        if find(u) != find(v):
            union(u, v)
            mst.append((u, v, w))
    return mst

mst_kruskal = kruskal(departments, edges)
print("\nKruskal's MST:")
for edge in mst_kruskal:
    print(edge)

def prim_simple(departments, adj_list):
    start = departments[0]
    visited = set([start])
    mst = []
    while len(visited) < len(departments):
        min_edge = None
        for src in visited:
            for dest, dist in adj_list[src]:
                if dest not in visited:
                    if min_edge is None or dist < min_edge[2]:
                        min_edge = (src, dest, dist)
        if min_edge:
            _, dest, _ = min_edge
            visited.add(dest)
            mst.append(min_edge)
    return mst

mst_prim = prim_simple(departments, adj_list)
print("\nPrim's MST:")
for edge in mst_prim:
    print(edge)

def draw_graph(nodes, edges, title):
    G = nx.Graph()
    G.add_weighted_edges_from(edges)
    pos = nx.spring_layout(G)
    labels = nx.get_edge_attributes(G, 'weight')
    plt.figure(figsize=(6, 4))
    nx.draw(G, pos, with_labels=True, node_color='lightblue',
            node_size=1200, font_size=10, font_weight='bold', edgecolors='black')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.title(title)
    plt.show()

draw_graph(departments, edges, "Original Campus Graph")
draw_graph(departments, mst_kruskal, "MST by Kruskal")
draw_graph(departments, mst_prim, "MST by Prim")
