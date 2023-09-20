from typing import Tuple, List
class Graph :
    def __init__(self, N:int, M:int, edge : List[Tuple[int, int, int]]) :
        self.num_vertex=N # vertices correspond to 0~N-1
        self.num_edge=M
        self.edge=edge #List[Tuple[int, int, int]]
        self.dist=[] #to record distance
        self.predecessor=[] #to record predecessor in the path

    def initialize_single_source(self, source:int) :
        self.dist=[float('inf')]*self.num_vertex #to record distance
        self.predecessor=[None]*self.num_vertex #to record predecessor in the path
        self.dist[source]=0#source point distance=0

    # #function to map name int to idx int
    # def idx(self, name:int):
    #     return (name-1)

    def relax(self, u:int, v:int, weight_from_u_to_v:int) :
        if self.dist[v]>self.dist[u]+weight_from_u_to_v :
            self.dist[v]=self.dist[u]+weight_from_u_to_v
            self.predecessor[v]=u

    def add_edge(self, edge : Tuple[int, int, int]) :
        self.edge.append(edge)
        self.num_edge+=1

    def print_path(self, start:int, end:int) :
        if start==end :
            print(f'({start})', end="")
        elif self.predecessor[end]==None :
            print(f'(-1) No path.', end="")
        else :
            self.print_path(start, self.predecessor[end])
            print(f'->({end})', end="")        


    def bellman_ford_alg(self, source:int) :
        self.initialize_single_source(source)
        for i in range(self.num_vertex-1) :
            for (start, end, weight) in self.edge :
                self.relax(start, end, weight)
        for (start, end, weight) in self.edge :
            if self.dist[end] > self.dist[start]+weight :
                return -1
        for i in range(1, self.num_vertex, 1) :
            if self.dist[i]==float('inf') : print(-1)
            else :
                print(self.dist[i])
        # for i in range(self.num_vertex) :
        #     print(f'({source})->({i}) distance=({self.dist[i]})\t',end="")
        #     self.print_path(source, i)
        #     print()


#py파일용
if __name__ == "__main__":
    n, m = map(int, input().split())
    edge = []
    
    for _ in range(m):
        start, end, weight = map(int, input().split())
        edge.append((start-1,end-1,weight)) 
    graph=Graph(n, m, edge)
    graph.bellman_ford_alg(0)
