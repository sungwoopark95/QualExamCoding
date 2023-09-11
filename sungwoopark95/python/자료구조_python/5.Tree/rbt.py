########################## 파이썬 용 rbt 코드 ###########################3
class RedBlackTree:
    RED = 0
    BLACK = 1

    class Node:
        def __init__(self, data, color, parent=None):
            self.data = data
            self.color = color
            self.parent = parent
            self.left = None
            self.right = None

    def __init__(self):
        self.NIL_LEAF = self.Node(None, self.BLACK)
        self.root = self.NIL_LEAF

    def insert(self, data):
        new_node = self.Node(data, self.RED, parent=None)
        # 처음 삽입되는 노드는 루트 노드가 됩니다.
        if self.root == self.NIL_LEAF:
            self.root = new_node
            self.root.color = self.BLACK
            self.root.parent = None
            self.root.left = self.NIL_LEAF
            self.root.right = self.NIL_LEAF
            return

        # 노드를 삽입할 위치 찾기
        node = self.insert_node(self.root, new_node)
        # 레드-블랙 트리의 규칙에 따라 트리를 재조정
        self.fix_insert(node)

    def insert_node(self, root, node):
        if root == self.NIL_LEAF:
            return node

        if node.data < root.data:
            root.left = self.insert_node(root.left, node)
            root.left.parent = root
            return root
        else:
            root.right = self.insert_node(root.right, node)
            root.right.parent = root
            return root

    def rotate_left(self, node):
        right_temp = node.right
        node.right = right_temp.left
        if right_temp.left != self.NIL_LEAF:
            right_temp.left.parent = node
        right_temp.parent = node.parent
        if node.parent is None:
            self.root = right_temp
        elif node == node.parent.left:
            node.parent.left = right_temp
        else:
            node.parent.right = right_temp
        right_temp.left = node
        node.parent = right_temp

    def rotate_right(self, node):
        left_temp = node.left
        node.left = left_temp.right
        if left_temp.right != self.NIL_LEAF:
            left_temp.right.parent = node
        left_temp.parent = node.parent
        if node.parent is None:
            self.root = left_temp
        elif node == node.parent.right:
            node.parent.right = left_temp
        else:
            node.parent.left = left_temp
        left_temp.right = node
        node.parent = left_temp

    def fix_insert(self, k):
        while k.parent.color == self.RED:
            if k.parent == k.parent.parent.right:
                uncle = k.parent.parent.left
                if uncle.color == self.RED:
                    uncle.color = self.BLACK
                    k.parent.color = self.BLACK
                    k.parent.parent.color = self.RED
                    k = k.parent.parent
                else:
                    if k == k.parent.left:
                        k = k.parent
                        self.rotate_right(k)
                    k.parent.color = self.BLACK
                    k.parent.parent.color = self.RED
                    self.rotate_left(k.parent.parent)
            else:
                uncle = k.parent.parent.right
                if uncle.color == self.RED:
                    uncle.color = self.BLACK
                    k.parent.color = self.BLACK
                    k.parent.parent.color = self.RED
                    k = k.parent.parent
                else:
                    if k == k.parent.right:
                        k = k.parent
                        self.rotate_left(k)
                    k.parent.color = self.BLACK
                    k.parent.parent.color = self.RED
                    self.rotate_right(k.parent.parent)
            if k == self.root:
                break
        self.root.color = self.BLACK

    def print_tree(self, node, indent="", last=True):
        if node != self.NIL_LEAF:
            print(indent, end="")
            if last:
                print("R----", end="")
                indent += "     "
            else:
                print("L----", end="")
                indent += "|    "
            color = "BLACK" if node.color == self.BLACK else "RED"
            print(f"{node.data} ({color})")
            self.print_tree(node.left, indent, False)
            self.print_tree(node.right, indent, True)

# 사용 예시
tree = RedBlackTree()
tree.insert(5)
tree.insert(3)
tree.insert(8)
tree.insert(2)
tree.insert(4)
tree.insert(7)
tree.insert(9)
tree.print_tree(tree.root)








# ########################### c++ 변환용 코드 ###############################
# class RBT:
#     class Node:
#         def __init__(self, key, color, parent=None, left=None, right=None):
#             self.key = key
#             self.color = color
#             self.parent = parent
#             self.left = left
#             self.right = right

#     # RBT의 초기화 함수
#     def __init__(self):
#         self.Tnil = self.Node(0, 'COLOR_BLACK')
#         self.root = self.Tnil

#     def InsertFixUp(self, z):
#         while z.parent.color == 'COLOR_RED':
#             if z.parent == z.parent.parent.right:
#                 y = z.parent.parent.left  # y는 z의 삼촌 노드
#                 if y.color == 'COLOR_RED':
#                     # case 1
#                     y.color = 'COLOR_BLACK'
#                     z.parent.color = 'COLOR_BLACK'
#                     z.parent.parent.color = 'COLOR_RED'
#                     z = z.parent.parent
#                 else:
#                     if z == z.parent.left:
#                         # case 2
#                         z = z.parent
#                         self.RightRotate(z)
#                     # case 3
#                     z.parent.color = 'COLOR_BLACK'
#                     z.parent.parent.color = 'COLOR_RED'
#                     self.LeftRotate(z.parent.parent)
#             else:  # 대칭적인 경우
#                 y = z.parent.parent.right
#                 if y.color == 'COLOR_RED':
#                     y.color = 'COLOR_BLACK'
#                     z.parent.color = 'COLOR_BLACK'
#                     z.parent.parent.color = 'COLOR_RED'
#                     z = z.parent.parent
#                 else:
#                     if z == z.parent.right:
#                         z = z.parent
#                         self.LeftRotate(z)
#                     z.parent.color = 'COLOR_BLACK'
#                     z.parent.parent.color = 'COLOR_RED'
#                     self.RightRotate(z.parent.parent)
#             if z == self.root:
#                 break
#         self.root.color = 'COLOR_BLACK'

#     def LeftRotate(self, x):
#         y = x.right
#         x.right = y.left
#         if y.left != self.Tnil:
#             y.left.parent = x
#         y.parent = x.parent
#         if x.parent is None:
#             self.root = y
#         elif x == x.parent.left:
#             x.parent.left = y
#         else:
#             x.parent.right = y
#         y.left = x
#         x.parent = y

#     def RightRotate(self, x):
#         y = x.left
#         x.left = y.right
#         if y.right != self.Tnil:
#             y.right.parent = x
#         y.parent = x.parent
#         if x.parent is None:
#             self.root = y
#         elif x == x.parent.right:
#             x.parent.right = y
#         else:
#             x.parent.left = y
#         y.right = x
#         x.parent = y

#     def DeleteFixUp(self, x):
#         # x가 root이거나 x의 색상이 Red가 될 때까지 반복
#         while x != self.root and x.color == 'COLOR_BLACK':
#             if x == x.parent.left:
#                 w = x.parent.right
#                 if w.color == 'COLOR_RED':
#                     w.color = 'COLOR_BLACK'
#                     x.parent.color = 'COLOR_RED'
#                     self.LeftRotate(x.parent)
#                     w = x.parent.right
#                 if w.left.color == 'COLOR_BLACK' and w.right.color == 'COLOR_BLACK':
#                     w.color = 'COLOR_RED'
#                     x = x.parent
#                 else:
#                     if w.right.color == 'COLOR_BLACK':
#                         w.left.color = 'COLOR_BLACK'
#                         w.color = 'COLOR_RED'
#                         self.RightRotate(w)
#                         w = x.parent.right
#                     w.color = x.parent.color
#                     x.parent.color = 'COLOR_BLACK'
#                     w.right.color = 'COLOR_BLACK'
#                     self.LeftRotate(x.parent)
#                     x = self.root
#             else:  # 대칭적인 경우
#                 w = x.parent.left
#                 if w.color == 'COLOR_RED':
#                     w.color = 'COLOR_BLACK'
#                     x.parent.color = 'COLOR_RED'
#                     self.RightRotate(x.parent)
#                     w = x.parent.left
#                 if w.right.color == 'COLOR_BLACK' and w.right.color == 'COLOR_BLACK':
#                     w.color = 'COLOR_RED'
#                     x = x.parent
#                 else:
#                     if w.left.color == 'COLOR_BLACK':
#                         w.right.color = 'COLOR_BLACK'
#                         w.color = 'COLOR_RED'
#                         self.LeftRotate(w)
#                         w = x.parent.left
#                     w.color = x.parent.color
#                     x.parent.color = 'COLOR_BLACK'
#                     w.left.color = 'COLOR_BLACK'
#                     self.RightRotate(x.parent)
#                     x = self.root
#         x.color = 'COLOR_BLACK'

#     def Transplant(self, u, v):
#         if u.parent is None:
#             self.root = v
#         elif u == u.parent.left:
#             u.parent.left = v
#         else:
#             u.parent.right = v
#         v.parent = u.parent

#     def _print(self, root, indent, last):
#         if root != self.Tnil:
#             print(indent, end="")
#             if last:
#                 print("R----", end="")
#                 indent += "     "
#             else:
#                 print("L----", end="")
#                 indent += "|    "
#             color = "BLACK" if root.color == 'COLOR_BLACK' else "RED"
#             print(f"{root.key} ({color})")
#             self._print(root.left, indent, False)
#             self._print(root.right, indent, True)

#     def Print(self):
#         if self.root:
#             self._print(self.root, "", True)
