INF = float('inf')

def bellman_ford():
    dist = [INF] * (n+1)
    dist[1] = 0
    cycle = False

    for k in range(1, n+1):
        for i in range(1, n+1):
            for next, next_cost in edge[i]:
                if dist[i] != INF and dist[next] > dist[i] + next_cost:
                    dist[next] = dist[i] + next_cost
                    if k == n:
                        cycle = True

    if cycle:
        print(-1)
    else:
        for i in range(2, n+1):
            print(dist[i] if dist[i] != INF else -1)

if __name__ == "__main__":
    n, m = map(int, input().split())
    edge = [[] for _ in range(n+1)]
    
    for _ in range(m):
        a, b, c = map(int, input().split())
        edge[a].append((b, c))
    
    bellman_ford()
