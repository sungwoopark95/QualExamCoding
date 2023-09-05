"""
BST를 List로 바꾸는 함수
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def bst_to_list(root):
    result = []

    def in_order_traversal(node):
        if not node:
            return
        in_order_traversal(node.left)
        result.append(node.val)
        in_order_traversal(node.right)

    in_order_traversal(root)
    return result
