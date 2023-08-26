from collections import deque

class Graph:
    def __init__(self, filename):
        self.vertex = {}
        f = open(filename, 'r')
        for line in f:
            line = line.strip().split(",")
            # get key and item in integer
            key = int(line[0])
            item = int(line[1])
            # if key and item does not exist in vertex 
            # initialize both
            if ((key not in self.vertex.keys()) & (item not in self.vertex.keys())):
                self.vertex[key] = [item]
                self.vertex[item] = []
            # if key is not in vertex, initialize it
            elif key not in self.vertex.keys():
                self.vertex[key] = [item]
            # if key exists, but item is not in vertex
            # add to the existing value and initialize item
            elif ((key in self.vertex.keys())&(item not in self.vertex.keys())):
                self.vertex[key].append(item)
                self.vertex[item] = []
            else:
                self.vertex[key].append(item)
    
    def check_distance(self,x, y, max_distance):
        # Initialize list of visited nodes
        visited = []
        # Initialize queue
        queue = deque()
        # initialize distance
        distance = 0
    
        # if start and end is same return True
        # since max_distance is >= 1
        if x == y:
            return True
    
        # add start value to queue
        queue.append(x)
    
        while queue:
            # Since FIFO, pop to the left
            node = queue.popleft()
            # add 1 to distance
            distance = distance + 1
            # if distance is bigger than max distance stop
            if distance > max_distance:
                return False
            if node not in visited:
                # get adjacent vertices
                adj = self.vertex[node]
                # create a path using each node
                for i in adj:
                    # first check if the that adjacent vertex is same
                    if i == y:
                        return True
                    # else append the adjacent vertex
                    queue.append(i)
                # add the visited node
                visited.append(node)
        # if not exist, return False
        return False