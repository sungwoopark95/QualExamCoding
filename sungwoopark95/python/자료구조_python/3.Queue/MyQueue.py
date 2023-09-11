class BaseArray:
    def __init__(self, capacity=100):
        self.capacity = capacity
        self.mem = [0] * capacity

    def put(self, index, val):
        self.mem[index] = val

    def get(self, index):
        return self.mem[index]

    def getCapacity(self):
        return self.capacity


class MyQueue(BaseArray):
    def __init__(self, capacity):
        super().__init__(capacity)
        self.start = 0
        self.end = 0

    def length(self):
        return self.end - self.start

    def enqueue(self, n):
        if self.length() < self.getCapacity():
            if self.start > 0:
                for i in range(self.start, self.end):
                    self.put(i - self.start, self.get(i))
                self.end -= self.start
                self.start = 0
            self.put(self.end, n)
            self.end += 1
        else:
            print("cannot push")

    def dequeue(self):
        val = -1
        if self.length() > 0:
            val = self.get(self.start)
            self.start += 1
        return val
    
    def front(self):
        return self.mem[0]