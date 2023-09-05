"""
[List를 BST로 변환하는 함수]
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# TreeNode로 반환
def list_to_bst(nums: list):
    # 먼저 list 순서대로 정렬하기
    nums = sorted(nums)
    
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