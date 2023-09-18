"""
[rightmost와 leftmost (non null)포함 사이 node 개수가 최대인 것 찾기]
Given the root of a binary tree, 
    return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes 
    (the leftmost and rightmost non-null nodes), 
    where the null nodes between the end-nodes that 
    would be present in a complete binary tree extending down to that 
    level are also counted into the length calculation.
    
            1 (ID:0)
         /           \
(ID:0)  2              3 (ID: 1)
       / \              \
(ID:0)4   5(ID:1) (ID:2) 7 (ID:3)
현재 노드의 ID * 2 와 현재 노드의 ID * 2 + 1은 
전형적인 이진 트리(Binary Tree)에서 배열을 사용하여 트리를 구현할 때 사용되는 인덱싱 방식

root = [1,3,2,5,3,None,9]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
4

root = [1,3,2,5,None,None,9,6,None,7]
tree = list_to_btree(root)
widthOfBinaryTree(tree)
7
"""
from collections import deque

# TreeNode 클래스를 정의합니다.
class TreeNode:
    # 초기화 함수로 노드 값을 설정하고 왼쪽, 오른쪽 자식 노드를 초기화합니다.
    def __init__(self, val=0, left=None, right=None):
        self.val = val       # 노드의 값을 저장하는 변수
        self.left = left     # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right   # 오른쪽 자식 노드를 가리키는 포인터

############## 완벽한 list 형태 (꽉 찬 형태)가 아니어도 binary tree로 구현 가능 ####################
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

def widthOfBinaryTree(root: TreeNode) -> int:
    # 트리의 루트가 없으면, 최대 너비는 0입니다.
    if not root:
        return 0
    
    # 큐를 초기화합니다. 각 원소는 (노드, ID)의 튜플 형태입니다.
    queue = deque([(root, 0)])
    max_width = 0
    
    while queue:
        level_length = len(queue)
        _, first_id = queue[0] # 현재 레벨의 첫 번째 노드의 ID
        
        # 현재 레벨의 모든 노드를 처리합니다.
        for _ in range(level_length):
            node, curr_id = queue.popleft()
            
            # 왼쪽 자식 노드가 있으면, 큐에 추가하고 ID는 현재 노드의 ID * 2로 설정합니다.
            if node.left:
                queue.append((node.left, curr_id * 2))
            # 오른쪽 자식 노드가 있으면, 큐에 추가하고 ID는 현재 노드의 ID * 2 + 1로 설정합니다.
            if node.right:
                queue.append((node.right, curr_id * 2 + 1))
        
        # 현재 레벨의 너비를 계산하고, 최대 너비를 업데이트합니다.
        max_width = max(max_width, curr_id - first_id + 1)
    
    return max_width