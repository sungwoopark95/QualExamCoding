class Stack:
    # 스택 클래스 초기화 메소드. 기본 스택 크기는 100으로 설정
    def __init__(self, MAX_SIZE=100):
        self.list = []  # 스택의 항목들을 저장할 리스트
        self.MAX_SIZE = MAX_SIZE  # 스택의 최대 크기 설정

    # 주어진 항목의 인덱스를 찾아 반환하는 메소드. 없으면 -1을 반환
    def find_index(self, item):
        if item in self.list:  # 해당 항목이 리스트에 존재하는 경우
            return self.list.index(item)  # 해당 항목의 인덱스 반환
        else:
            return -1  # 항목이 존재하지 않는 경우 -1 반환

    # 스택에 항목을 추가하는 메소드
    def push(self, item):
        if len(self.list) == self.MAX_SIZE:  # 스택이 꽉 찼을 경우
            raise Exception("Stack Overflow.")  # 에러 발생
        else:
            self.list.append(item)  # 스택에 항목 추가

    # 스택의 최상단 항목을 제거하고 반환하는 메소드
    def pop(self):
        if not self.list:  # 스택이 비어있을 경우
            raise Exception("Error: No item exists in the list")  # 에러 발생
        return self.list.pop()  # 스택의 최상단 항목 제거 및 반환

    # 스택의 모든 항목을 출력하는 메소드
    def print(self):
        print(", ".join(map(str, self.list)))  # 스택의 모든 항목 출력

    # 현재 스택에 저장된 항목 수를 반환하는 메소드
    def get_size(self):
        return len(self.list)  # 스택의 현재 크기 반환

    # 특정 인덱스의 항목을 반환하는 메소드
    def get_item(self, index):
        return self.list[index]  # 주어진 인덱스의 항목 반환

    # 두 스택을 병합하는 메소드. 중복 항목은 제거
    def __iadd__(self, other):
        for item in other.list:  # 다른 스택의 항목들을 순회
            if item not in self.list:  # 해당 항목이 현재 스택에 없는 경우
                self.push(item)  # 현재 스택에 항목 추가
        return self  # 현재 스택 반환
    
    
#------------------ temp로 따로 object 할당해서 진행한 것 ----------------#
    def __iadd__(self, other):
        # 두 스택을 병합하는 연산을 수행한다.
        temp = Stack()
        for item in self.items:
            temp.push(item)

        for i in range(other.get_size()):
            item = other.get_item(i)
            if self.find_index(item) == -1:
                temp.push(item)

        self.items = temp.items
        self.size = temp.size
        return self


    # 두 스택이 같은지 비교하는 메소드
    def __eq__(self, other):
        return self.list == other.list  # 두 스택의 리스트가 같은지 비교


if __name__ == '__main__':
    s1, s2, s3 = Stack(), Stack(), Stack()

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

    print("s1 == s2 ?", s1 == s2)  # 출력: s1 == s2 ? False

    print(s1.pop())  # 출력: 5
    print(s1.pop())  # 출력: 3
    print(s2.pop())  # 출력: 5
    print("s1 == s2 ?", s1 == s2)  # 출력: s1 == s2 ? True

    print(s2.pop())  # 출력: 2
    print(s2.pop())  # 출력: 1
    try:
        print(s2.pop())  # 에러 발생
    except Exception as e:
        print(e)
