from enum import Enum

class Color(Enum):
    BLACK = 0
    RED = 1

class RBT:
    class Node:
        def __init__(self, key, parent=None, left=None, right=None, color=Color.BLACK):
            self.key = key
            self.parent = parent
            self.left = left
            self.right = right
            self.color = color
    
    def __init__(self):
        self.Tnil = self.Node(0, color=Color.BLACK)
        self.root = self.Tnil

    def GetRoot(self):
        return self.root

    def Insert(self, key):
        z = self.Node(key, None, self.Tnil, self.Tnil, Color.RED)

        x = self.root
        y = None

        while x != self.Tnil:
            y = x
            if z.key < x.key:
                x = x.left
            else:
                x = x.right

        z.parent = y

        if y is None:
            self.root = z
        elif z.key < y.key:
            y.left = z
        else:
            y.right = z

        if z.parent is None:
            z.color = Color.BLACK
            return

        if z.parent.parent is None:
            return

        self.InsertFixUp(z)

    def Delete(self, z):
        x = None
        y = z
        y_original_color = y.color
        if z.left == self.Tnil:
            x = z.right
            self.Transplant(z, z.right)
        elif z.right == self.Tnil:
            x = z.left
            self.Transplant(z, z.left)
        else:
            y = self.Minimum(z.right)
            y_original_color = y.color
            x = y.right
            if y.parent == z:
                x.parent = y
            else:
                self.Transplant(y, y.right)
                y.right = z.right
                y.right.parent = y

            self.Transplant(z, y)
            y.left = z.left
            y.left.parent = y
            y.color = z.color
            # No explicit delete in Python; the garbage collector will handle it.

        if y_original_color == Color.BLACK:
            self.DeleteFixUp(x)

    def Preorder(self, node):
        if node != self.Tnil:
            print(node.key, end=" ")
            self.Preorder(node.left)
            self.Preorder(node.right)

    def Inorder(self, node):
        if node != self.Tnil:
            self.Inorder(node.left)
            print(node.key, end=" ")
            self.Inorder(node.right)

    def Postorder(self, node):
        if node != self.Tnil:
            self.Postorder(node.left)
            self.Postorder(node.right)
            print(node.key, end=" ")
            
    def Search(self, node, key):
        if key == node.key:
            return node
        elif node == self.Tnil:
            return None

        if key < node.key:
            return self.Search(node.left, key)
        else:
            return self.Search(node.right, key)

    def Maximum(self, node):
        while node.right != self.Tnil:
            node = node.right
        return node

    def Minimum(self, node):
        while node.left != self.Tnil:
            node = node.left
        return node

    def Successor(self, x):
        if x.right != self.Tnil:
            return self.Minimum(x.right)

        y = x.parent
        while y != self.Tnil and x == y.right:
            x = y
            y = y.parent
        return y

    def Predecessor(self, x):
        if x.left != self.Tnil:
            return self.Maximum(x.left)

        y = x.parent
        while y != self.Tnil and x == y.left:
            x = y
            y = y.parent
        return y
    
    def InsertFixUp(self, z):
        while z.parent.color == Color.RED:
            if z.parent == z.parent.parent.right:
                y = z.parent.parent.left
                if y.color == Color.RED:
                    # case 1
                    y.color = Color.BLACK
                    z.parent.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    z = z.parent.parent
                else:
                    if z == z.parent.left:
                        # case 2
                        z = z.parent
                        self.RightRotate(z)
                    # case 3
                    z.parent.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    self.LeftRotate(z.parent.parent)
            else:
                y = z.parent.parent.right

                if y.color == Color.RED:
                    y.color = Color.BLACK
                    z.parent.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    z = z.parent.parent
                else:
                    if z == z.parent.right:
                        z = z.parent
                        self.LeftRotate(z)
                    z.parent.color = Color.BLACK
                    z.parent.parent.color = Color.RED
                    self.RightRotate(z.parent.parent)

            if z == self.root:
                break

        self.root.color = Color.BLACK

    def LeftRotate(self, x):
        y = x.right
        x.right = y.left
        if y.left != self.Tnil:
            y.left.parent = x
        y.parent = x.parent
        if x.parent == None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    def RightRotate(self, x):
        y = x.left
        x.left = y.right
        if y.right != self.Tnil:
            y.right.parent = x
        y.parent = x.parent
        if x.parent == None:
            self.root = y
        elif x == x.parent.right:
            x.parent.right = y
        else:
            x.parent.left = y
        y.right = x
        x.parent = y
        
    def DeleteFixUp(self, x):
        while x != self.root and x.color == Color.BLACK:
            if x == x.parent.left:
                w = x.parent.right
                if w.color == Color.RED:
                    w.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.LeftRotate(x.parent)
                    w = x.parent.right

                if w.left.color == Color.BLACK and w.right.color == Color.BLACK:
                    w.color = Color.RED
                    x = x.parent
                else:
                    if w.right.color == Color.BLACK:
                        w.left.color = Color.BLACK
                        w.color = Color.RED
                        self.RightRotate(w)
                        w = x.parent.right

                    w.color = x.parent.color
                    x.parent.color = Color.BLACK
                    w.right.color = Color.BLACK
                    self.LeftRotate(x.parent)
                    x = self.root
            else:
                w = x.parent.left
                if w.color == Color.RED:
                    w.color = Color.BLACK
                    x.parent.color = Color.RED
                    self.RightRotate(x.parent)
                    w = x.parent.left

                if w.left.color == Color.BLACK and w.right.color == Color.BLACK:
                    w.color = Color.RED
                    x = x.parent
                else:
                    if w.left.color == Color.BLACK:
                        w.right.color = Color.BLACK
                        w.color = Color.RED
                        self.LeftRotate(w)
                        w = x.parent.left

                    w.color = x.parent.color
                    x.parent.color = Color.BLACK
                    w.left.color = Color.BLACK
                    self.RightRotate(x.parent)
                    x = self.root
        x.color = Color.BLACK

    def Transplant(self, u, v):
        if u.parent == None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        v.parent = u.parent

    def _print(self, root, indent, last):
        if root != self.Tnil:
            print(indent, end="")
            if last:
                print("R----", end="")
                indent += "     "
            else:
                print("L----", end="")
                indent += "|    "

            sColor = "BLACK" if root.color == Color.BLACK else "RED"
            print(f"{root.key} ({sColor})")
            self._print(root.left, indent, False)
            self._print(root.right, indent, True)

    def Print(self):
        if self.GetRoot() != None:
            self._print(self.GetRoot(), "", True)

            
if __name__ == "__main__":
    rbt = RBT()
    rbt.Insert(8)
    rbt.Insert(18)
    rbt.Insert(5)
    rbt.Insert(15)
    rbt.Insert(17)
    rbt.Insert(25)
    rbt.Insert(40)
    rbt.Insert(80)

    print("========== Initial RBT ==========")
    rbt.Print()

    # find and delete the node whose key is 25
    target = rbt.Search(rbt.GetRoot(), 25)
    if target:
        rbt.Delete(target)

    print("======= After deleting 25 =======" )
    rbt.Print()
