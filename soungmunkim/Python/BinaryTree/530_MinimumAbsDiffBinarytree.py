"""
[BST에서 인접한 두 노드간의 abs 차이가 mim인 것 반환하기]

Given the root of a Binary Search Tree (BST), 
    return the minimum absolute difference between the values of any two different nodes in the tree.

Input: root = [4,2,6,1,3]
Output: 1

Input: root = [1,0,48,null,null,12,49]
Output: 1
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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

# 구체적으로는 각 노드의 값과 해당 서브트리 내에서 가장 큰 노드 값 또는 가장 작은 노드 값 간의 차이를 계산
# 이진 검색 트리 (BST)에서 최소 절대 차이 계산 함수
def getMinimumDifference(root):
    def inorder_traversal(node):
        nonlocal prev, min_diff
        if not node:
            return
        
        # 중위 순회
        inorder_traversal(node.left)
        
        if prev is not None:
            min_diff = min(min_diff, abs(node.val - prev)) # max로 바꾸면 max abs diff
        
        prev = node.val
        
        inorder_traversal(node.right)
    
    prev = None  # 이전 노드의 값
    min_diff = float('inf')  # 최소 절대 차이를 저장할 변수
    
    inorder_traversal(root)
    
    return min_diff

if __name__ == "__main__":
    root = [1,0,48,None,None,12,49]
    head = list_to_bst(root)
    result = getMinimumDifference(head)
    print(result)