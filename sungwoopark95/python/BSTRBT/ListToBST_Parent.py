"""
[BST에서 특정 노드 삭제하기]
!! TreeNode class만 주어졌을 때 !!
> deleteNode(list, key:int) 형태임

< 구헌된 함수들 >
1. create_BST
    Insert
2. transplant
3. delete
4. seach
5. minimum
5. print_BST
    inorder
    level order(왼쪽에서 오른쪽)
    null 표시하게 프린트 or null 없이 프린트

root = [5,3,6,2,4,None,7]
key = 3
deleteNode(root, key) # [5, 4, 6, 2, 'Null', 'Null', 7]

root = [5,3,6,2,4,None,7]
key = 0
deleteNode(root,key) # [5, 3, 6, 2, 4, 'Null', 7]
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

###########################(delete 위해) transplant 함수 구현 ########################
def transplant(root:TreeNode, u:TreeNode, v:TreeNode): 
    if not u.parent:         # u가 루트이면
        root = v             # 루트를 v로 교체

    elif u == u.parent.left: # u가 왼쪽 자식이면
        u.parent.left = v    # 부모의 왼쪽 자식을 v로
        
    else:                    # u가 오른쪽 자식이면
        u.parent.right = v   # 부모의 오른쪽 자식을 v로
        
    if v:
        v.parent = u.parent  # v의 부모를 u의 부모로 설정
    return root              # 수정된 루트 반환

############################ delete 함수 구현 ########################
def delete(root:TreeNode, key:TreeNode):
    z = search(root, key)    # 삭제할 노드 검색
    # 해당 노드를 찾으면
    if z:             
         # 왼쪽 자식이 없으면       
        if not z.left:      
            root = transplant(root, z, z.right)
            
        # 오른쪽 자식이 없으면
        elif not z.right:    
            root = transplant(root, z, z.left)
            
        # 두 자식이 모두 있으면 
        else:                
            y = minimum(z.right)
            if y.parent != z:
                root = transplant(root, y, y.right)
                y.right = z.right
                y.right.parent = y
                
            root = transplant(root, z, y)
            y.left = z.left
            y.left.parent = y
            
    return root              # 수정된 루트 반환

###################### (delete or get target 찾는) search 함수 구현 ########################
def search(node:TreeNode, key:int):
    while node and key != node.key:  # 노드가 존재하고 키 값이 일치하지 않으면
        if key < node.key:     # 키 값이 현재 노드보다 작으면 왼쪽으로
            node = node.left
        else:                  # 그렇지 않으면 오른쪽으로
            node = node.right
    return node               # 노드 반환 (찾지 못하면 None)

###################### minimum node 찾는 함수 구현 ########################
def minimum(node:TreeNode):
    while node.left:          # 가장 왼쪽 노드를 찾기 위해 왼쪽으로 이동
        node = node.left
    return node               # 가장 작은 값을 가진 노드 반환


################# 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 ##################
# def print_BST(node:TreeNode):
#     if not node:              # 노드가 없으면 빈 리스트 반환
#         return []

#     result = []
#     queue = [node]            # 초기 큐에 루트 노드 저장

#     while queue:              # 큐가 빌 때까지 반복
#         current = queue.pop(0) # 큐에서 노드 꺼내기
     
#         result.append(current.key)  # 결과 리스트에 키 값 추가

#         if current.left:      # 왼쪽 자식이 있으면 큐에 추가
#             queue.append(current.left)
#         if current.right:     # 오른쪽 자식이 있으면 큐에 추가
#             queue.append(current.right)

#     return result             # 결과 리스트 반환


############ (None node Null로 프린트) 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 #################
def print_BST(node:TreeNode):
    if not node:              # 노드가 없으면 빈 리스트 반환
        return []

    result = []
    queue = [node]            # 초기 큐에 루트 노드 저장

    while queue:              # 큐가 빌 때까지 반복
        current = queue.pop(0) # 큐에서 노드 꺼내기
        
        if current:
            result.append(current.key)
            # None인 자식도 큐에 추가하여 후에 'Null'로 표시할 수 있도록 함
            queue.append(current.left)
            queue.append(current.right)
            
        else:
            result.append('Null')

    # 마지막에 연속된 'Null' 제거
    while result and result[-1] == 'Null':
        result.pop()

    return result             # 결과 리스트 반환


################ in order는 sorted list 형태로 나옴 ############
# def print_BST(node):
#     result = []

#     def inorder(n):
#         if n:
#             inorder(n.left)
#             result.append(n.key)
#             inorder(n.right)

#     inorder(node)
#     return result


def deleteNode(root:list, key:int):
    tree = create_BST(root)
    result_tree = delete(tree, key)
    
    return print_BST(result_tree)


if __name__ == "__main__":
    source = [10, 4, 5, 20, 8, None, 1, 3, None, 35, 7, 13, 17]
    root = create_BST(source)
    print(print_BST(root))