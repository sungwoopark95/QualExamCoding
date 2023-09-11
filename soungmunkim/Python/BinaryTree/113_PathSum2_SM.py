"""
Given the root of a binary tree and an integer targetSum, 
return all root-to-leaf paths where the sum of the node values in the path equals targetSum. 
Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. 
A leaf is a node with no children.

Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22

Input: root = [1,2,3], targetSum = 5
Output: []
"""

from collections import deque
# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

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

# binary tree root -> leaf 각 paths 찾아주는 함수 
# bst에서도 사용 가능
def findPaths(root, current_path, paths):
    if not root:
        return

    # 현재 경로에 노드 값을 추가
    current_path.append(root.val)

    # 리프 노드에 도달하면 현재 경로를 결과에 추가
    if not root.left and not root.right:
        paths.append(list(current_path))
    else:
        findPaths(root.left, current_path, paths)
        findPaths(root.right, current_path, paths)

    # 백트래킹: 현재 노드를 방문을 마치고 부모 노드로 돌아가기 위해 경로에서 제거
    current_path.pop()

def hasPathSum2(root, target_sum):
    
    # find all binary tree paths
    paths = []
    tree = list_to_btree(root)
    findPaths(tree, [], paths)
    
    # 합이 target sum이 되는 pahts 찾기
    ans = []
    for path in paths:
        if sum(path) == target_sum:
            ans.append(path)

    return ans