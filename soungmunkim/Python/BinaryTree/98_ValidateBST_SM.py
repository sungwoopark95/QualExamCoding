"""
[현재 binary tree가 BST인지 확인하는 코드 ]
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

The left  subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Input: root = [2,1,3]
Output: true

Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.
"""

import sys

# TreeNode 클래스를 정의합니다.
class TreeNode:
    # 초기화 함수로 노드 값을 설정하고 왼쪽, 오른쪽 자식 노드를 초기화합니다.
    def __init__(self, val=0, left=None, right=None):
        self.val = val       # 노드의 값을 저장하는 변수
        self.left = left     # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right   # 오른쪽 자식 노드를 가리키는 포인터

# 숫자 리스트를 이진 트리로 변환하는 함수
def list_to_btree(nums: list):
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


"""
루트 노드는 아무런 제한 없이 어떤 값을 가질 수 있기 때문에, lower를 음의 무한대로, upper를 양의 무한대로 설정합니다.
왼쪽 서브트리로 이동할 때는 현재 노드의 값(node.val)이 최대값(upper)이 되고, lower는 그대로 유지됩니다. 
    이는 왼쪽 서브트리의 모든 노드들이 현재 노드의 값보다 작아야 하기 때문입니다.
오른쪽 서브트리로 이동할 때는 현재 노드의 값(node.val)이 최소값(lower)이 되고, upper는 그대로 유지됩니다. 
    이는 오른쪽 서브트리의 모든 노드들이 현재 노드의 값보다 커야 하기 때문입니다.
"""
def isValidBST(root: list):
    # list를 Binary tree로 변환 (TreeNode)
    tree = list_to_btree(root)
    
    # dfs로 돌면서 binary search tree인지 체크하기
    lower = float("-inf")
    upper = float("inf")
    
    def dfs_BT(node, lower, upper):
        #tree가 없으니 BST라고 가정함 (base case)
        if node is None:
            return True
        # 현재 node값이 현재 최소값보다 작으면 (범위 밖에 있으면)
        if node.val <= lower:
            return False
        # 현재 node값이 현재 최대값보다 크면 (범위 밖에 있으면)
        elif node.val >= upper:
            return False
        
        # right에서 upper는 얼마나 크든 상관 없지만 right node가 현재 노드보다 작으면 안되서 설정함
        return (dfs_BT(node.right, node.val, upper) and dfs_BT(node.left, lower, node.val))
    
    return dfs_BT(tree, lower, upper)