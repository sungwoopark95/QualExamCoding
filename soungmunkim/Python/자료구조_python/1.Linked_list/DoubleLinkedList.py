class Node:
    def __init__(self, strData=None):
        self.strData = strData  # 문자열 데이터
        self.prev = None  # 이전 노드 포인터
        self.next = None  # 다음 노드 포인터


class DLinkedList:
    def __init__(self):
        self.header = Node()  # 헤더 노드 생성
        self.trailer = Node()  # 트레일러 노드 생성
        self.header.next = self.trailer  # 헤더의 다음은 트레일러
        self.trailer.prev = self.header  # 트레일러의 이전은 헤더

    def isEmpty(self):
        return self.header.next == self.trailer  # 헤더 다음이 트레일러면 true

    def getFront(self):
        return self.header.next.strData  # 헤더 다음 노드의 데이터 반환

    def getBack(self):
        return self.trailer.prev.strData  # 트레일러 이전 노드의 데이터 반환

    def addFront(self, e):
        self.add(self.header, e)  # 헤더 뒤에 새 노드 추가

    def addBack(self, e):
        self.add(self.trailer.prev, e)  # 트레일러 앞에 새 노드 추가

    def add(self, v, e):
        u = Node(e)  # 새 노드 생성
        u.next = v.next  # 새 노드의 다음을 v의 다음으로 설정
        u.prev = v  # 새 노드의 이전을 v로 설정
        v.next.prev = u  # v 다음 노드의 이전을 새 노드로 설정
        v.next = u  # v의 다음을 새 노드로 설정

    def removeFront(self):
        self.remove(self.header.next)  # 헤더 다음 노드 삭제

    def removeBack(self):
        self.remove(self.trailer.prev)  # 트레일러 이전 노드 삭제

    def remove(self, v):
        v.prev.next = v.next  # v의 이전 노드의 다음을 v의 다음 노드로 설정
        v.next.prev = v.prev  # v의 다음 노드의 이전을 v의 이전 노드로 설정

    def TraverseForward(self):
        v = self.header.next  # 첫 번째 노드부터 시작
        while v.next:  # 다음 노드가 None이 아니면 계속
            print(v.strData, end=" ")  # 현재 노드의 데이터 출력
            v = v.next  # 다음 노드로 이동

    def TraverseBackward(self):
        v = self.trailer.prev  # 마지막 노드부터 시작
        while v.prev:  # 이전 노드가 None이 아니면 계속
            print(v.strData, end=" ")  # 현재 노드의 데이터 출력
            v = v.prev  # 이전 노드로 이동


if __name__ == "__main__":
    DL = DLinkedList()

    DL.addFront("3")
    DL.addFront("5")
    DL.addFront("8")
    DL.addFront("10")

    # 3 -> 5 -> 8 -> 10
    DL.TraverseBackward()
    print()

    # 10 -> 8 -> 5 -> 3
    DL.TraverseForward()
    print()

    DL.removeBack()
    DL.removeBack()

    # 10 -> 8
    DL.TraverseForward()
    print()
