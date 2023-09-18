class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        
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

def isSymmetric(root: TreeNode) -> bool:
    def isSame(root1:TreeNode, root2:TreeNode):
        # 두 노드 모두 None인 경우: 두 노드는 동일하므로 True 반환
        if not root1 and not root2:
            return True
        # 둘 중 하나의 노드만 None인 경우: 두 트리는 동일하지 않으므로 False 반환
        if not root1 or not root2:
            return False
        # 두 노드의 값이 다른 경우: 두 트리는 동일하지 않으므로 False 반환
        if root1.val != root2.val:
            return False
        # 위의 조건들을 모두 통과한 경우, 재귀적으로 왼쪽 서브트리와 오른쪽 서브트리가 동일한지 확인
        # 두 서브트리 모두 동일해야만 True 반환
        return isSame(root1.left, root2.right) and isSame(root1.right, root2.left)
    return isSame(root.left, root.right)


if __name__ == "__main__":
    root1 = [1,2,2,3,4,4,3]
    root1 = list_to_btree(root1)
    print(isSymmetric(root1))
    
    root2 = [1,2,2,None,3,None,3]
    root2 = list_to_btree(root2)
    print(isSymmetric(root2))