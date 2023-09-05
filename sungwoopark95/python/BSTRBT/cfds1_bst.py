class BST:
    class Node:
        def __init__(self, key):
            self.key = key
            self.parent = None
            self.left = None
            self.right = None

    def __init__(self):
        self.root = None
        
    def getRoot(self):
        return self.root

    def insert(self, key):
        z = self.Node(key)
        x = self.root
        y = None

        while x:
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

    def transplant(self, u, v):
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v

        if v:
            v.parent = u.parent

    def delete(self, z):
        if not z.left:
            self.transplant(z, z.right)
        elif not z.right:
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

    def preorder(self, node):
        if node:
            print(node.key, end=" ")
            self.preorder(node.left)
            self.preorder(node.right)

    def inorder(self, node):
        if node:
            self.inorder(node.left)
            print(node.key, end=" ")
            self.inorder(node.right)

    def postorder(self, node):
        if node:
            self.postorder(node.left)
            self.postorder(node.right)
            print(node.key, end=" ")

    def search(self, node, key):
        if not node or key == node.key:
            return node
        if key < node.key:
            return self.search(node.left, key)
        else:
            return self.search(node.right, key)

    def maximum(self, node):
        while node.right:
            node = node.right
        return node

    def minimum(self, node):
        while node.left:
            node = node.left
        return node

    def successor(self, x):
        if x.right:
            return self.minimum(x.right)
        y = x.parent
        while y and x == y.right:
            x = y
            y = y.parent
        return y

    def predecessor(self, x):
        if x.left:
            return self.maximum(x.left)
        y = x.parent
        while y and x == y.left:
            x = y
            y = y.parent
        return y

    def _print(self, root, indent="", last=True):
        if root:
            print(indent, end="")
            if last:
                print("└────", end="")
                indent += "     "
            else:
                print("├────", end="")
                indent += "|    "
            print(root.key)
            self._print(root.left, indent, False)
            self._print(root.right, indent, True)

    def print(self):
        if self.root:
            self._print(self.root)


if __name__ == "__main__":
    bst = BST()
    bst.insert(8)
    bst.insert(18)
    bst.insert(5)
    bst.insert(15)
    bst.insert(17)
    bst.insert(25)
    bst.insert(40)
    bst.insert(80)

    print("========== Initial BST ==========")
    bst.print()

    # find and delete the node whose key is 25
    target = bst.search(bst.getRoot(), 25)
    if target is not None:
        bst.delete(target)

    print("======= After deleting 25 =======")
    bst.print()