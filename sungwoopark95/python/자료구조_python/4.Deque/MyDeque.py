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


class MyDeque(BaseArray):
    def __init__(self, capacity):
        super().__init__(capacity)

    def push_back(self, n):
        if self.length() < self.getCapacity() and self.end < self.getCapacity():
            self.put(self.end, n)
            self.end += 1
        else:
            print("cannot push")

    def push_front(self, n):
        if self.length() < self.getCapacity():
            if self.start > 0:
                self.put(self.start-1, n)
                self.start -= 1
            else:
                for i in range(self.end-1, -1, -1):
                    self.put(i+1, self.get(i))
                self.end += 1
                self.put(0, n)
        else:
            print("cannot push")

    def pop_back(self):
        val = -1
        if self.length() > 0:
            val = self.get(self.end - 1)
            self.end -= 1
        return val

    def pop_front(self):
        return super().dequeue()