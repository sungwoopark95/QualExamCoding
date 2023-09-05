"""
[Linked list에서 cluster 찾기]
프로그램의 첫번째 입력(Argument)으로는 파일 경로를 받은 후 파일을 읽어 Linked list를 생성한다. 
두번째 입력값(Argument)부터는 임의의 정수들을 입력받는다. 
그런 다음 입력으로 받은 정수들이 파일로부터 생성된 Linked list에서 연결되어 있는지를 확인한다. 
서로 연결되어 있는 정수 그룹의 개수를 출력하는 프로그램을 완성하여라. 

 “1 2 3 4 5”가 입력되어 있다고 가정하자. 
그렇다면 Skeleton code를 통해 1->2->3->4->5인 Linked list가 생성될 것이다. 
이 경우의 프로그램 실행 예시는 다음과 같다. 

TestCase1)
>>./P3 inputList.txt 1 2 3
>>1
설명: Linked List가 1-2-3-4-5이고 입력으로 1,2,3이 들어왔다. 
Linked List 내에서 1,2,3은 모두 Link로 연결되어 하나의 그룹(Cluster)을 형성한다. 따라서 그룹의 개수는 1이다.

TestCase2)
>>./P3 inputList.txt 1 3 5
>>3	
설명: Linked List가 1-2-3-4-5이고 입력으로 1,3,5가 들어왔다. 
주어진 Linked List 내에서 1,3,5 사이에는 Link가 존재하지 않는다. 따라서 1,3,5는 별도의 그룹을 각각 형성하므로 그룹의 개수는 3이다. 
"""

class Node:
    def __init__(self, data):
        self.data = data   # 노드에 저장될 데이터 값
        self.next = None   # 다음 노드를 가리키는 포인터

def FindCluster(nums):
    # 연결 리스트 생성
    head = None  # 연결 리스트의 헤드
    prev = None  # 이전 노드

    for val in nums:
        curr = Node(val)   # 새 노드 생성

        if prev is None:
            head = curr    # 첫 번째 노드면 head로 설정
        else:
            prev.next = curr   # 이전 노드의 next를 현재 노드로 설정

        prev = curr   # 이전 노드 업데이트

    numConnected = 0   # 연결된 "클러스터"의 수

    curr = head
    while curr:
        if curr.data in nums:  # 숫자가 리스트 안에 있으면
            numConnected += 1
        curr = curr.next

    return numConnected  # 결과 반환

# 예시
nums = [1, 2, 3, 4, 5]
print(FindCluster(nums))


#--------------------------------------- 사용자에게 숫자 입력받았을 때 ------------------------------#
# class Node:
#     def __init__(self, data):
#         self.data = data   # 노드에 저장될 데이터 값
#         self.next = None   # 다음 노드를 가리키는 포인터

# input_str = input("Enter the numbers separated by spaces: ")   # 사용자로부터 입력 받기

# # 입력을 공백으로 분할하고 연결 리스트 생성
# head = None  # 연결 리스트의 헤드
# prev = None  # 이전 노드

# for val_str in input_str.split():
#     val = int(val_str)
#     curr = Node(val)   # 새 노드 생성

#     if prev is None:
#         head = curr    # 첫 번째 노드면 head로 설정
#     else:
#         prev.next = curr   # 이전 노드의 next를 현재 노드로 설정

#     prev = curr   # 이전 노드 업데이트

# numConnected = 0   # 연결된 "클러스터"의 수
# numbers = list(map(int, input_str.split()))

# curr = head
# while curr:
#     if curr.data in numbers:  # 숫자가 리스트 안에 있으면
#         numConnected += 1
#     curr = curr.next

# print(numConnected)  # 결과 출력
