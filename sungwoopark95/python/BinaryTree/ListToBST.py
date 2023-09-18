from collections import deque

# Definition for TreeNode.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

############################# 컴기 버전 #############################
# Create a BST from a list, then return root node
def create_linked_bst(arr: list) -> TreeNode:
    if len(arr) < 1: 
        return None
    n = iter(arr)
    tree = TreeNode(next(n))
    fringe = deque([tree])
    
    while True:
        head = fringe.popleft()
        try:
            l = next(n)
            if l is not None:
                head.left = TreeNode(l)
            else:
                head.left = None
            fringe.append(head.left)
            r = next(n)
            if r is not None:
                head.right = TreeNode(r)
            else:
                head.right = None
            head.right = TreeNode(r) if r != None else None
            fringe.append(head.right)
        except StopIteration:
            break
    return tree
###################################################################

############################# 성문 버전 #############################
# Create a BST from a list, then return root node
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
###################################################################

####################### Binary Tree To List #######################
def BST_to_list(node:TreeNode) -> list:
    if not node:              # 노드가 없으면 빈 리스트 반환
        return []

    result = []
    queue = [node]            # 초기 큐에 루트 노드 저장

    while queue:              # 큐가 빌 때까지 반복
        current = queue.pop(0) # 큐에서 노드 꺼내기
        
        if current:
            result.append(current.val)
            # None인 자식도 큐에 추가하여 후에 'Null'로 표시할 수 있도록 함
            queue.append(current.left)
            queue.append(current.right)
            
        else:
            result.append('Null')

    # 마지막에 연속된 'Null' 제거
    while result and result[-1] == 'Null':
        result.pop()

    return result             # 결과 리스트 반환
###################################################################

######################## Binary Tree Print ########################
def print_BST(node:TreeNode) -> None:
    if not node:              # 노드가 없으면 빈 리스트 반환
        return []

    result = []
    queue = [node]            # 초기 큐에 루트 노드 저장

    while queue:              # 큐가 빌 때까지 반복
        current = queue.pop(0) # 큐에서 노드 꺼내기
        
        if current:
            result.append(current.val)
            # None인 자식도 큐에 추가하여 후에 'Null'로 표시할 수 있도록 함
            queue.append(current.left)
            queue.append(current.right)
            
        else:
            result.append('Null')

    # 마지막에 연속된 'Null' 제거
    while result and result[-1] == 'Null':
        result.pop()
    print(result)
###################################################################

####################### TreeNode 형태로 프린트 #######################
def print_dict(root:TreeNode) -> None:
    def TreeNode_String(root:TreeNode) -> str:
        if root is None:
            return 'None'
        result = f"{{'val': {root.val}, "
        left_string = TreeNode_String(root.left)
        right_string = TreeNode_String(root.right)
        result += f"'left': {left_string}, 'right': {right_string}}}"
        return result
    print(TreeNode_String(root))
###################################################################

####################### 두 tree가 같은지 다른지 반환하는 함수 #######################
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
#############################################################################

if __name__ == "__main__":
    source = [3,4,5,1,2]
    root = create_linked_bst(source)
    print(root)
    print_BST(root)
    print_dict(root)