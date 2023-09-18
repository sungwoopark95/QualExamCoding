"""
[node key의 빈도가 most frequently인 node key를 list로 반환하는 문제]
해당 bst는 left subtree는 해당 root와 key 값이 작거나 같고
right subtree도 해당 root와 key 값이 크거나 같다.

이럴때, node key의 빈도가 most frequently인 node key를 list로 반환하는 문제

Given the root of a binary search tree (BST) with duplicates, 
return all the mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

root = [1,None,2,2]
tree = list_to_btree(root)
findMode(tree)
>>> [2]

root = [0]
tree1 = list_to_btree(root)
findMode(tree1)
>>> [0]
"""
from typing import List

class TreeNode:
    # 초기화 함수로 노드 값을 설정하고 왼쪽, 오른쪽 자식 노드를 초기화합니다.
    def __init__(self, val=0, left=None, right=None):
        self.val = val       # 노드의 값을 저장하는 변수
        self.left = left     # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right   # 오른쪽 자식 노드를 가리키는 포인터

# TreeNode로 반환
def list_to_bst(nums: list):
    # None이 아닌 값을 필터링하여 새로운 리스트를 생성합니다.
    filtered_nums = []
    for x in nums:
        if x is not None:
            filtered_nums.append(x)

    # 필터링된 리스트를 정렬합니다.
    sorted_nums = sorted(filtered_nums)

    # 정렬된 리스트를 다시 nums 변수에 할당합니다.
    nums = sorted_nums
    
    # Base case
    if not nums:
        return None

    # 중앙 값을 찾아 트리의 root로 설정
    mid = len(nums) // 2
    root = TreeNode(nums[mid])

    # 재귀적으로 왼쪽과 오른쪽 하위 트리를 구성
    root.left = list_to_bst(nums[:mid])
    root.right = list_to_bst(nums[mid+1:])

    return root

def findMode(root: TreeNode) -> List[int]:
        if not root:
            return None

        # bfs로 tree돌기 (graph처럼 생각하기)
        q = [root]
        cnt = dict() # node key 별로 빈도수 저장할 dict
    
        while q:
            cur = q.pop(0)
            # 현재 key count 체크
            if cur.val not in cnt:
                cnt[cur.val] = 1
            else:
                cnt[cur.val] += 1

            # 만약 다음 오른쪽 노드가 있으면 q에 넣기
            if cur.right:
                q.append(cur.right)
            # 만약 다음 왼쪽 노드가 있으면 q에 넣기
            if cur.left:
                q.append(cur.left)

        mode = -1
        ans = []
        # most frequent한 횟수 찾기
        for val in cnt.values():
            if val >= mode:
                mode = val
                
        # 해당 횟수 갖은 key를 ans에 append하기
        for key, val in cnt.items():
            if val == mode:
                ans.append(key)
        return ans
    
### ------------------------- 챗지피티 답 버전 ------------------------------- ##
"""
inorder로 순회하면서 node 빈도 체크하는 방식
"""
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right


# def findMode(self, root: TreeNode):
#     # 빈도수를 저장할 딕셔너리와 결과 리스트 초기화
#     count = {}
#     result = []
    
#     # 중위 순회 함수
#     def inorder(node):
#         if not node:
#             return
#         inorder(node.left)
       
#         #count.get(node.val, 0): count 딕셔너리에서 node.val 키의 값을 가져옵니다. 
#         # 만약 node.val 키가 딕셔너리에 없으면, 대신에 0을 반환
#         count[node.val] = count.get(node.val, 0) + 1  # 현재 노드의 값의 빈도수를 1 증가
#         inorder(node.right)
    
#     # 트리를 중위 순회하며 각 값의 빈도수를 계산
#     inorder(root)
    
#     # 가장 높은 빈도수 찾기
#     max_count = max(count.values())
    
#     # 가장 높은 빈도수를 가진 값을 결과 리스트에 추가
#     for key, value in count.items():
#         if value == max_count:
#             result.append(key)
    
#     return result
