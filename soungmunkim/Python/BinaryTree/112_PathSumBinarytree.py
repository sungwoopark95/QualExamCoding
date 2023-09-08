"""
[root부터 마지막까지 한 path 합이 targetsum과 같은지]

Given the root of a binary tree and an integer targetSum, 
    return true if the tree has a root-to-leaf path 
    such that adding up all the values along the path equals targetSum.
    
root = [5,4,8,11,None,13,4,7,2,None,None,None,1]
targetSum = 22
head = list_to_btree(root)
hasPathSum(head, targetSum) # True

Explanation: The root-to-leaf path with the target sum is shown.

root = [1,2,3]
targetSum = 5
head1 = list_to_btree(root)
hasPathSum(head1, targetSum) # False

There is no root-to-leaf path with sum = 5.
"""

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

def hasPathSum(root, target_sum):
    if not root:
        return False

    # 현재 노드가 leaf 노드이고 남은 합이 현재 노드의 값과 같다면
    if not root.left and not root.right and root.val == target_sum:
        return True

    # 현재 노드의 값을 현재 남은 합에서 뺍니다.
    target_sum -= root.val

    # 왼쪽 서브트리나 오른쪽 서브트리 중 하나라도 합을 만족하는 경로가 있다면 True를 반환합니다.
    return hasPathSum(root.left, target_sum) or hasPathSum(root.right, target_sum)