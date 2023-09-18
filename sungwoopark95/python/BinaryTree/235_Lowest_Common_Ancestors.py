# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


####################### List에서 BST 만들기 (Insert함수 이용) #######################
def create_BST(input_list: list) -> TreeNode:
    root = None                     # 초기 루트는 None
    for item in input_list:         # 입력 리스트의 각 항목에 대해
        root = insert(root, item)   # 트리에 항목 삽입
    return root                      # 루트 반환

############################ insert 함수 구현 ############################
def insert(root:TreeNode, val:int) -> TreeNode:
    if val is None:           # 키 값이 None인 경우 그대로 루트 반환
        return root

    if not root:              # 루트가 없으면 새 노드 생성 후 반환
        return TreeNode(val)

    if val < root.val:     # 키 값이 현재 루트보다 작으면 왼쪽 서브트리로
        # 왼쪽 자식이 없으면 새 노드를 왼쪽 자식으로
        if root.left is None: 
            root.left = TreeNode(val)
        # 왼쪽 자식이 있으면 재귀적으로 왼쪽 서브트리에 삽입 
        else:                 
            insert(root.left, val)
            
    # 키 값이 현재 루트보다 크거나 같으면 오른쪽 서브트리로      
    else:                   
        if root.right is None: # 오른쪽 자식이 없으면 새 노드를 오른쪽 자식으로
            root.right = TreeNode(val)
         # 오른쪽 자식이 있으면 재귀적으로 오른쪽 서브트리에 삽입
        else:                 
            insert(root.right, val)
    return root              # 수정된 루트 반환

############################ 원래 함수 ############################
def lowestCommonAncestor(root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
    # 두 노드 p와 q 중 작은 값을 가진 노드를 min_node로, 큰 값을 가진 노드를 max_node로 지정합니다.
    if p.val < q.val:
        min_node, max_node = p, q
    else:
        min_node, max_node = q, p
    
    # min_node와 max_node로 이동하는 경로를 저장할 두 리스트를 초기화합니다.
    min_parents, max_parents = [], []
    
    # root에서 시작하여 min_node까지의 경로를 찾습니다.
    curr = root
    # curr이 min_node에 도달할 때까지 반복합니다.
    while curr.val != min_node.val:
        # 현재 노드를 경로에 추가합니다.
        min_parents.append(curr)
        # min_node의 값이 현재 노드의 값보다 작으면 왼쪽으로 이동합니다.
        if min_node.val < curr.val:
            curr = curr.left
        # min_node의 값이 현재 노드의 값보다 크면 오른쪽으로 이동합니다.
        elif min_node.val > curr.val:
            curr = curr.right
    # min_node를 경로에 추가합니다.
    min_parents.append(curr)
    print([root.val for root in min_parents])

    # root에서 시작하여 max_node까지의 경로를 찾습니다.
    curr = root
    # curr이 max_node에 도달할 때까지 반복합니다.
    while curr.val != max_node.val:
        # 현재 노드를 경로에 추가합니다.
        max_parents.append(curr)
        # max_node의 값이 현재 노드의 값보다 작으면 왼쪽으로 이동합니다.
        if max_node.val < curr.val:
            curr = curr.left
        # max_node의 값이 현재 노드의 값보다 크면 오른쪽으로 이동합니다.
        elif max_node.val > curr.val:
            curr = curr.right
    # max_node를 경로에 추가합니다.
    max_parents.append(curr)
    print([root.val for root in max_parents])

    # 두 경로 중 더 긴 경로와 더 짧은 경로를 파악합니다.
    if len(max_parents) < len(min_parents):
        common_len = len(max_parents)
        longer, smaller = min_parents, max_parents
    else:
        common_len = len(min_parents)
        longer, smaller = max_parents, min_parents
    
    # 두 경로의 공통된 노드들을 저장하는 리스트를 초기화합니다.
    common = []
    
    # 더 짧은 경로의 노드가 더 긴 경로에 포함되어 있는지 확인하고, 포함된다면 공통 노드 리스트에 추가합니다.
    for i in range(common_len):
        if smaller[i] in longer:
            common.append(smaller[i])

    # 가장 마지막에 추가된 공통 노드, 즉 LCA를 반환합니다.
    return common[-1]

############################ root가 list로 주어진 경우 ############################
def lowestCommonAncestorList(root: list, p: int, q: int) -> TreeNode:
    root = create_BST(root)
    p, q = TreeNode(p), TreeNode(q)
    
    # 두 노드 p와 q 중 작은 값을 가진 노드를 min_node로, 큰 값을 가진 노드를 max_node로 지정합니다.
    if p.val < q.val:
        min_node, max_node = p, q
    else:
        min_node, max_node = q, p
    
    # min_node와 max_node로 이동하는 경로를 저장할 두 리스트를 초기화합니다.
    min_parents, max_parents = [], []
    
    # root에서 시작하여 min_node까지의 경로를 찾습니다.
    curr = root
    # curr이 min_node에 도달할 때까지 반복합니다.
    while curr.val != min_node.val:
        # 현재 노드를 경로에 추가합니다.
        min_parents.append(curr)
        # min_node의 값이 현재 노드의 값보다 작으면 왼쪽으로 이동합니다.
        if min_node.val < curr.val:
            curr = curr.left
        # min_node의 값이 현재 노드의 값보다 크면 오른쪽으로 이동합니다.
        elif min_node.val > curr.val:
            curr = curr.right
    # min_node를 경로에 추가합니다.
    min_parents.append(curr)
    print([root.val for root in min_parents])

    # root에서 시작하여 max_node까지의 경로를 찾습니다.
    curr = root
    # curr이 max_node에 도달할 때까지 반복합니다.
    while curr.val != max_node.val:
        # 현재 노드를 경로에 추가합니다.
        max_parents.append(curr)
        # max_node의 값이 현재 노드의 값보다 작으면 왼쪽으로 이동합니다.
        if max_node.val < curr.val:
            curr = curr.left
        # max_node의 값이 현재 노드의 값보다 크면 오른쪽으로 이동합니다.
        elif max_node.val > curr.val:
            curr = curr.right
    # max_node를 경로에 추가합니다.
    max_parents.append(curr)
    print([root.val for root in max_parents])

    # 두 경로 중 더 긴 경로와 더 짧은 경로를 파악합니다.
    if len(max_parents) < len(min_parents):
        common_len = len(max_parents)
        longer, smaller = min_parents, max_parents
    else:
        common_len = len(min_parents)
        longer, smaller = max_parents, min_parents
    
    # 두 경로의 공통된 노드들을 저장하는 리스트를 초기화합니다.
    common = []
    
    # 더 짧은 경로의 노드가 더 긴 경로에 포함되어 있는지 확인하고, 포함된다면 공통 노드 리스트에 추가합니다.
    for i in range(common_len):
        if smaller[i] in longer:
            common.append(smaller[i])

    # 가장 마지막에 추가된 공통 노드, 즉 LCA를 반환합니다.
    return common[-1]

if __name__ == "__main__":
    root = [6,2,8,0,4,7,9,None,None,3,5]
    p = 3
    q = 5
    
    print(lowestCommonAncestorList(root, p, q).val)