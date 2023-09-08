from collections import deque

# Definition for TreeNode.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
        
    def printTree(self):
        result = list()
        thislevel = [self]
        while thislevel:
            nextlevel = list()
            none_list=1
            for n in thislevel:
                if n !=None:
                    none_list=0
                    break
            if none_list==1:
                return result
                        
            for n in thislevel:
                if n != None: 
                    result.append(n.val)
                    nextlevel.append(n.left)
                    nextlevel.append(n.right)
                else:
                    result.append(None)
                    nextlevel.append(None)
                    nextlevel.append(None)
                    
            thislevel = nextlevel
        return result

#Create a BST from a list, then return root node
def create_linked_bst(arr: list):
    if len(arr) < 1: 
        return None
    n = iter(arr)
    tree = TreeNode(next(n))
    fringe = deque([tree])
    
    while True:
        head = fringe.popleft()
        try:
            l = next(n)
            head.left = TreeNode(l) if l != None else None
            fringe.append(head.left)
            r = next(n)
            head.right = TreeNode(r) if r != None else None
            fringe.append(head.right)
        except StopIteration:
            break
    return tree
