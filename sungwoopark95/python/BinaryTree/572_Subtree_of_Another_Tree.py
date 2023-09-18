# Definition for TreeNode.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        

def list_to_bst(nums: list) -> TreeNode:
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
    return isSame(root1.left, root2.left) and isSame(root1.right, root2.right)


def isSubTree(root:TreeNode, subRoot:TreeNode) -> bool:
    queue = [root]
    while queue:
        curr = queue.pop(0)
        # bfs하면서 현재 노드의 value가 subroot의 value와 같은지 확인하고,
        # 같으면 서로 같은 tree인지 체크
        if curr.val == subRoot.val:
            # 같으면 바로 true 반환
            if isSame(curr, subRoot):
                return True
        if curr.left:
            queue.append(curr.left)
        if curr.right:
            queue.append(curr.right)
    # while이 끝났다는 것은 서로 같은 tree가 없다는 의미
    return False