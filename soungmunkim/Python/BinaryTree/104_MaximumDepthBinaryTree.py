"""
[Binary tree maximum depth 찾기]
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes 
    along the longest path from the root node down to the farthest leaf node.


root = [3, 9, 20, None, None, 15, 7]
head = list_to_btree(root)
maxDepth(head) # 3

Input: root = [1,null,2]
Output: 2
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 숫자 리스트를 이진 트리로 변환하는 함수
def list_to_btree(nums: list) -> TreeNode:
    if not nums:
        return None

    # 노드들을 저장할 큐를 생성합니다.
    queue = []
    
    # 루트 노드를 생성하고 큐에 추가합니다.
    root = TreeNode(nums[0])
    queue.append(root)
    
    # 노드들을 연결하기 위해 리스트를 순회합니다.
    i = 1
    while queue and i < len(nums):
        # 현재 노드를 큐에서 꺼냅니다.
        current = queue.pop(0)
        
        # 왼쪽 자식이 있다면, 연결하고 큐에 추가합니다.
        if nums[i] is not None:
            left_child = TreeNode(nums[i])
            current.left = left_child
            queue.append(left_child)
        i += 1

        # 오른쪽 자식이 있다면, 연결하고 큐에 추가합니다.
        if i < len(nums) and nums[i] is not None:
            right_child = TreeNode(nums[i])
            current.right = right_child
            queue.append(right_child)
        i += 1

    return root

# 이진 트리의 최대 깊이를 계산하는 함수
def maxDepth(root: TreeNode) -> int:
    level = 0  # 트리의 레벨을 저장하는 변수 초기화

    if root is None:
        return 0  # 루트 노드가 없으면 트리의 레벨은 0이므로 0 반환

    q = [root]  # 큐를 사용하여 노드 순회를 위한 리스트 초기화

    while q:
        for i in range(len(q)):
            root = q.pop(0)  # 큐에서 노드를 하나 꺼냄

            if root.left is not None:
                q.append(root.left)  # 현재 노드의 왼쪽 자식을 큐에 추가

            if root.right is not None:
                q.append(root.right)  # 현재 노드의 오른쪽 자식을 큐에 추가

        level += 1  # 현재 레벨의 노드를 모두 처리하면 레벨 증가

    return level  # 최대 깊이(레벨) 반환