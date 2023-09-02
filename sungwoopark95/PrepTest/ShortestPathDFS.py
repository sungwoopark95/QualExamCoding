from typing import List

def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
    # construct the adjacent list
    self.adj = dict()
    for e in edges:
        x, y, w = e
        if x not in self.adj:
            self.adj[x] = [(y, w)]
        else:
            self.adj[x].append((y, w))

        if y not in self.adj:
            self.adj[y] = [(x, w)]
        else:
            self.adj[y].append((x, w))
    
    # edge case
    if n > len(self.adj.keys()):
        nones = [i for i in range(n) if i not in self.adj]
        return max(nones)

    def shortest_path(adj, start):
        distance = dict()
        for node in adj:
            distance[node] = float('inf')
        distance[start] = 0

        stack = [start]
        while stack:
            curr = stack.pop()
            for neighbor in adj[curr]:
                point, weight = neighbor
                if distance[point] >= distance[curr] + weight:
                    distance[point] = distance[curr] + weight
                    stack.append(point)
        return distance
    
    minimum_cities = dict()
    for node in self.adj:
        cnt = 0
        distance_dict = shortest_path(self.adj, edges, node)
        for point in distance_dict:
            if node == point:
                continue
            if distance_dict[point] <= distanceThreshold:
                cnt += 1
        minimum_cities[node] = cnt
    
    candidates = []
    min_cities = min(minimum_cities.values())
    for node in minimum_cities:
        if minimum_cities[node] == min_cities:
            candidates.append(node)

    return max(candidates)
