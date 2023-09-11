class Node:
    def __init__(self, key):
        self.key = key  # 노드에 저장될 값
        self.left = None  # 왼쪽 자식 노드
        self.right = None  # 오른쪽 자식 노드
        self.parent = None  # 부모 노드

class BST:
    def __init__(self):
        self.root = None  # BST의 루트 노드

    def insert(self, key):
        z = Node(key)  # 삽입할 노드 생성
        y = None  # y는 x의 부모 노드를 가리킬 것임
        x = self.root  # 루트에서 시작
        while x is not None:  # 삽입할 위치를 찾기 위해 트리를 탐색
            y = x
            if z.key < x.key:
                x = x.left
            else:
                x = x.right
        z.parent = y  # z의 부모를 y로 설정
        if y is None:  # 트리가 비어있으면 z를 루트로 설정
            self.root = z
        elif z.key < y.key:  # z의 키가 y의 키보다 작으면 왼쪽 자식으로 설정
            y.left = z
        else:  # 그렇지 않으면 오른쪽 자식으로 설정
            y.right = z

    def transplant(self, u, v):
        # u를 v로 대체하는 연산
        if u.parent is None:  # u가 루트 노드인 경우
            self.root = v
        elif u == u.parent.left:  # u가 왼쪽 자식인 경우
            u.parent.left = v
        else:  # u가 오른쪽 자식인 경우
            u.parent.right = v
        if v is not None:  # v가 None이 아닌 경우
            v.parent = u.parent

    def delete(self, z):
        # 노드 z를 삭제하는 연산
        if z.left is None:
            self.transplant(z, z.right)
        elif z.right is None:
            self.transplant(z, z.left)
        else:
            y = self.minimum(z.right)
            if y.parent != z:
                self.transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.transplant(z, y)
            y.left = z.left
            y.left.parent = y

    def inorder(self, node):
        # 중위 순회
        if node:
            self.inorder(node.left)
            print(node.key, end=' ')
            self.inorder(node.right)

    def preorder(self, node):
        # 전위 순회
        if node:
            print(node.key, end=' ')
            self.preorder(node.left)
            self.preorder(node.right)

    def postorder(self, node):
        # 후위 순회
        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.key, end=' ')

    def search(self, node, key):
        # key 값을 가진 노드를 탐색
        while node is not None and key != node.key:
            if key < node.key:
                node = node.left
            else:
                node = node.right
        return node

    def maximum(self, node):
        # 주어진 노드를 기준으로 가장 큰 키 값을 가진 노드를 찾는 연산
        while node.right:
            node = node.right
        return node

    def minimum(self, node):
        # 주어진 노드를 기준으로 가장 작은 키 값을 가진 노드를 찾는 연산
        while node.left:
            node = node.left
        return node

    def successor(self, x):
        # x의 후계자를 찾는 연산
        if x.right:
            return self.minimum(x.right)
        y = x.parent
        while y and x == y.right:
            x = y
            y = y.parent
        return y

    def predecessor(self, x):
        # x의 선조자를 찾는 연산
        if x.left:
            return self.maximum(x.left)
        y = x.parent
        while y and x == y.left:
            x = y
            y = y.parent
        return y

    def print_tree(self, node, level=0):
        # 트리를 시각적으로 출력
        if node:
            print(' ' * (level * 4) + str(node.key))
            if node.left or node.right:
                self.print_tree(node.left, level+1)
                self.print_tree(node.right, level+1)

    def print(self):
        # 트리 전체를 출력
        self.print_tree(self.root)

# ####################### 외부 함수들 구현 ##############################
# class Node:
#     def __init__(self, key):
#         self.key = key  # 노드에 저장될 값
#         self.left = None  # 왼쪽 자식 노드
#         self.right = None  # 오른쪽 자식 노드
#         self.parent = None  # 부모 노드

# class BST:
#     def __init__(self):
#         self.root = None  # BST의 루트 노드

# # 삽입 연산
# def insert(bst, key):
#     z = Node(key)
#     y = None
#     x = bst.root
#     while x is not None:
#         y = x
#         if z.key < x.key:
#             x = x.left
#         else:
#             x = x.right
#     z.parent = y
#     if y is None:
#         bst.root = z
#     elif z.key < y.key:
#         y.left = z
#     else:
#         y.right = z

# # 노드 교체 연산
# def transplant(bst, u, v):
#     if u.parent is None:
#         bst.root = v
#     elif u == u.parent.left:
#         u.parent.left = v
#     else:
#         u.parent.right = v
#     if v is not None:
#         v.parent = u.parent

# # 삭제 연산
# def delete(bst, z):
#     if z.left is None:
#         transplant(bst, z, z.right)
#     elif z.right is None:
#         transplant(bst, z, z.left)
#     else:
#         y = minimum(z.right)
#         if y.parent != z:
#             transplant(bst, y, y.right)
#             y.right = z.right
#             y.right.parent = y
#         transplant(bst, z, y)
#         y.left = z.left
#         y.left.parent = y

# # 중위 순회
# def inorder(node):
#     if node:
#         inorder(node.left)
#         print(node.key, end=' ')
#         inorder(node.right)

# # 전위 순회
# def preorder(node):
#     if node:
#         print(node.key, end=' ')
#         preorder(node.left)
#         preorder(node.right)

# # 후위 순회
# def postorder(node):
#     if node:
#         postorder(node.left)
#         postorder(node.right)
#         print(node.key, end=' ')

# # 키 값 탐색
# def search(bst, key):
#     node = bst.root
#     while node is not None and key != node.key:
#         if key < node.key:
#             node = node.left
#         else:
#             node = node.right
#     return node

# # 최대 키 값 탐색
# def maximum(node):
#     while node.right:
#         node = node.right
#     return node

# # 최소 키 값 탐색
# def minimum(node):
#     while node.left:
#         node = node.left
#     return node

# # 후계자 찾기
# def successor(x):
#     if x.right:
#         return minimum(x.right)
#     y = x.parent
#     while y and x == y.right:
#         x = y
#         y = y.parent
#     return y

# # 선조자 찾기
# def predecessor(x):
#     if x.left:
#         return maximum(x.left)
#     y = x.parent
#     while y and x == y.left:
#         x = y
#         y = y.parent
#     return y

# # 트리 출력
# def print_tree(node, level=0):
#     if node:
#         print(' ' * (level * 4) + str(node.key))
#         if node.left or node.right:
#             print_tree(node.left, level+1)
#             print_tree(node.right, level+1)

# def print_bst(bst):
#     print_tree(bst.root)
