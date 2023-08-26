"""
inputList.txt 파일에는 “1 2 3 4 5”가 입력되어 있다고 가정하자. 
그렇다면 Skeleton code를 통해 1->2->3->4->5인 Linked list가 생성될 것이다. (채점 시에는 예시와는 다른 파일을 사용할 것이다.) 

이 경우의 프로그램 실행 예시는 다음과 같다. 

예시1)
```py
>> l1 = create_linked_list([1, 2, 3, 4, 5])
>> P5(l1, [1, 2, 3])
1
```
설명: Linked List가 1-2-3-4-5이고 입력으로 1,2,3이 들어왔다. Linked List 내에서 1,2,3은 모두 Link로 연결되어 하나의 그룹(Cluster)을 형성한다. 따라서 그룹의 개수는 1이다.
"""
from LinkedListFunctions import ListNode, print_linked_list, create_linked_list
from typing import List

def P5(head:ListNode, nums:List[int]):
    curr = head
    # nums의 첫 번째 원소와 일치하는 노드를 찾을 때까지 연결 리스트를 순회
    while curr.val != nums[0]:
        curr = curr.next

    # curr는 이제 nums의 첫 번째 원소와 일치하는 노드를 가리킴
    cnt = 1  # 일치하는 연속된 노드의 개수
    curr = curr.next  # 다음 노드로 이동

    # nums의 나머지 원소들에 대해 연속적으로 일치하는 노드가 있는지 확인
    for i in range(1, len(nums)):
        if nums[i] == curr.val:
            curr = curr.next
            continue
        else:
            # nums[i]와 일치하는 노드를 찾을 때까지 연결 리스트를 순회
            while curr.val != nums[i] and curr is not None:
                curr = curr.next
            # 일치하는 노드를 찾았다면 cnt를 증가
            if curr is not None:
                cnt += 1

    return cnt  # 연속적으로 일치하는 노드의 개수 반환

if __name__ == "__main__":
    l1 = create_linked_list([1, 2, 3, 4, 5])
    print(P5(l1, [1, 2, 3]))
