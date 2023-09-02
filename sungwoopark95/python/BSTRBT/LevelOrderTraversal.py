from CreateBST import TreeNode, create_linked_bst
from typing import List

def P2(root:TreeNode) -> List[List[int]]:
    def levelOrder(root:TreeNode) -> List[List[int]]:
        visited = []
        if not root:
            return visited

        level_dict = dict()
        curNode = root
        queue = [root]
        level_dict[root] = 0
        levels = [0]
        while queue:
            curNode = queue.pop(0)
            if curNode.left:
                level_dict[curNode.left] = level_dict[curNode] + 1
                queue.append(curNode.left)
                if level_dict[curNode.left] not in levels:
                    levels.append(level_dict[curNode.left])
            if curNode.right:
                level_dict[curNode.right] = level_dict[curNode] + 1
                queue.append(curNode.right)
                if level_dict[curNode.right] not in levels:
                    levels.append(level_dict[curNode.right])
        
        for level in sorted(levels, reverse=True):
            level_list = []
            for key in level_dict.keys():
                if level_dict[key] == level:
                    level_list.append(key.val)
            visited.append(level_list)
        
        return visited

    return levelOrder(root)

if __name__ == "__main__":
    root = create_linked_bst ([3,9,20,None,None,15,7])
    print(P2(root))
