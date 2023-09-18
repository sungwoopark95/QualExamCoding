class Stack:
    def __init__(self, MAX_SIZE=100):  # 생성자
        self.size = 0  # 초기 스택 크기를 0으로 설정
        self.MAX_SIZE = MAX_SIZE  # 최대 크기를 설정값으로 설정
        self.p_list = [0] * MAX_SIZE  # 최대 크기만큼의 리스트 초기화

    def find_index(self, _item):  # 특정 항목의 인덱스를 찾는 함수
        try:
            return self.p_list.index(_item)
        except ValueError:
            return -1  # 항목을 찾지 못한 경우 -1 반환

    def push(self, _item):  # 항목을 스택에 추가하는 함수
        if self.size == self.MAX_SIZE:  # 스택이 꽉 찼을 때의 처리
            raise Exception("Stack Overflow.")  # 에러 메시지 출력
        self.p_list[self.size] = _item  # 항목을 스택의 맨 위에 추가
        self.size += 1

    def pop(self):  # 스택의 최상단 항목을 제거하고 반환하는 함수
        if self.size == 0:  # 스택이 비어있는 경우 처리
            raise Exception("Error: No item exists in the list")  # 에러 메시지 출력
        temp = self.p_list[self.size-1]  # 스택의 최상단 항목 값을 temp에 저장
        self.size -= 1
        return temp  # temp 값을 반환

    def get_size(self):  # 현재 스택에 저장된 항목 수를 반환하는 함수
        return self.size

    def get_item(self, _index):  # 특정 인덱스의 항목을 반환하는 함수
        return self.p_list[_index]

    def print(self):  # 스택의 모든 항목을 출력하는 함수
        print(", ".join(map(str, self.p_list[:self.size])))

    def __iadd__(self, s2):  # += 연산자 오버로딩 함수
        for i in range(s2.get_size()):
            item = s2.get_item(i)
            if self.find_index(item) == -1:
                self.push(item)  # 현재 스택에 해당 항목 추가
        return self

    def __eq__(self, s2):  # == 연산자 오버로딩 함수
        if self.size != s2.get_size():
            return False
        for i in range(self.size):
            if self.p_list[i] != s2.get_item(i):
                return False  # 두 스택은 동일하지 않음
        return True  # 모든 항목들이 동일하므로 두 스택은 동일

if __name__ == "__main__":
    s1 = Stack()
    s2 = Stack()

    s1.push(1)
    s1.push(2)
    s1.push(3)

    s2.push(1)
    s2.push(2)
    s2.push(5)

    s1.print()  # 출력: 1, 2, 3
    s2.print()  # 출력: 1, 2, 5

    s1 += s2
    s1.print()  # 출력: 1, 2, 3, 5
    s2.print()  # 출력: 1, 2, 5

    print("s1 == s2 ? {}".format(s1 == s2))  # 출력: s1 == s2 ? False

    print(s1.pop())  # 출력: 5
    print(s1.pop())  # 출력: 3
    print(s2.pop())  # 출력: 5
    print("s1 == s2 ? {}".format(s1 == s2))  # 출력: s1 == s2 ? True

    print(s2.pop())  # 출력: 2
    print(s2.pop())  # 출력: 1

    try:
        print(s2.pop())  # 에러: No item exists in the list
    except Exception as e:
        print(e)
