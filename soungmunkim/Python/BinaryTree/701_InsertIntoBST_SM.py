"""
[특정 key를 BST에 넣는 코드]

You are given the root node of a binary search tree (BST) and a value to insert into the tree. 
Return the root node of the BST after the insertion. 
It is guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as the tree remains a BST after insertion. You can return any of them.

root = [4,2,7,1,3]
val = 5
insertIntoBST(root, val)
>> [4, 2, 7, 1, 3, 5]

root = [4,2,7,1,3,None,None,None,None,None,None]
val = 5
insertIntoBST(root, val)
>> [4, 2, 7, 1, 3, 5]
"""


class TreeNode:
    def __init__(self, key):
        self.key = key          # 노드에 저장될 키 값
        self.parent = None      # 부모 노드
        self.left = None        # 왼쪽 자식 노드
        self.right = None       # 오른쪽 자식 노드

####################### List에서 BST 만들기 (Insert함수 이용) ####################
def create_BST(input_list: list):
    root = None                     # 초기 루트는 None
    
    for item in input_list:         # 입력 리스트의 각 항목에 대해
        root = insert(root, item)   # 트리에 항목 삽입
    return root                      # 루트 반환

############################ insert 함수 구현 ########################
def insert(root:TreeNode, key:int):
    if key is None:           # 키 값이 None인 경우 그대로 루트 반환
        return root

    if not root:              # 루트가 없으면 새 노드 생성 후 반환
        return TreeNode(key)

    if key < root.key:     # 키 값이 현재 루트보다 작으면 왼쪽 서브트리로
        # 왼쪽 자식이 없으면 새 노드를 왼쪽 자식으로
        if root.left is None: 
            root.left = TreeNode(key)
            root.left.parent = root 
            
        # 왼쪽 자식이 있으면 재귀적으로 왼쪽 서브트리에 삽입 
        else:                 
            insert(root.left, key)
            
    # 키 값이 현재 루트보다 크거나 같으면 오른쪽 서브트리로      
    else:                   
        if root.right is None: # 오른쪽 자식이 없으면 새 노드를 오른쪽 자식으로
            root.right = TreeNode(key)
            root.right.parent = root
            
         # 오른쪽 자식이 있으면 재귀적으로 오른쪽 서브트리에 삽입
        else:                 
            insert(root.right, key)

    return root              # 수정된 루트 반환

#------------------------- insert 함수 구현 (parent가 없을 때) --------------------------#
# def insert(root:TreeNode, key:int):
#     if key is None:           # 키 값이 None인 경우 그대로 루트 반환
#         return root

#     if not root:              # 루트가 없으면 새 노드 생성 후 반환
#         return TreeNode(key)

#     if key < root.key:     # 키 값이 현재 루트보다 작으면 왼쪽 서브트리로
#         # 왼쪽 자식이 없으면 새 노드를 왼쪽 자식으로
#         if root.left is None: 
#             root.left = TreeNode(key)
            
#         # 왼쪽 자식이 있으면 재귀적으로 왼쪽 서브트리에 삽입 
#         else:                 
#             insert(root.left, key)
            
#     # 키 값이 현재 루트보다 크거나 같으면 오른쪽 서브트리로      
#     else:                   
#         if root.right is None: # 오른쪽 자식이 없으면 새 노드를 오른쪽 자식으로
#             root.right = TreeNode(key)
            
#          # 오른쪽 자식이 있으면 재귀적으로 오른쪽 서브트리에 삽입
#         else:                 
#             insert(root.right, key)

#     return root              # 수정된 루트 반환


################# 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 ##################
def print_BST(node:TreeNode):
    if not node:              # 노드가 없으면 빈 리스트 반환
        return []

    result = []
    queue = [node]            # 초기 큐에 루트 노드 저장

    while queue:              # 큐가 빌 때까지 반복
        current = queue.pop(0) # 큐에서 노드 꺼내기
     
        result.append(current.key)  # 결과 리스트에 키 값 추가

        if current.left:      # 왼쪽 자식이 있으면 큐에 추가
            queue.append(current.left)
        if current.right:     # 오른쪽 자식이 있으면 큐에 추가
            queue.append(current.right)

    return result             # 결과 리스트 반환

def insertIntoBST(root:list, key:int):
    tree = create_BST(root)
    result = insert(tree, key)
    
    return print_BST(result)



