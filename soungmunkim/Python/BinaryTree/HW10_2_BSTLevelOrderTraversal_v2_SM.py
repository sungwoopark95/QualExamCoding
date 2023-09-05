"""
[Tree level 별 nodes 저장]
Binary tree 에 대하여 Bottom-up level order traversal 을 하고 return 하는 함수를 작성하시오. 
즉, Leaf 부터 Root 까지 각 level 에 대해, 왼쪽에서부터 오른쪽 순서로 저장되어야 한다.

• 이중리스트 형태로 return해야 하며, 같은 Depth인 Node들의 값이 같은 List에 저장되어야 한다.
• input 으로는 binary tree 의 root 가 주어진다.

TestCase 1)
     3 
    /\
   9  20 
      /\
     15 7
>>> root = create_linked_bst ([3,9,20,None,None,15,7])
>>> P2(root)
[[15, 7], [9, 20], [3]]
"""

#######################  BST helper code ####################
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    # list로 반환
    def printTree(self):
        # 결과를 저장할 리스트 초기화
        result = list()
        # 현재 레벨의 노드들을 저장
        thislevel = [self]
        
        # 노드가 있는 동안 계속 반복
        while thislevel:
            nextlevel = list()
            none_list = 1
            
            # 현재 레벨에 실제 노드가 있는지 확인
            for n in thislevel:
                if n != None:
                    none_list = 0
                    break
            if none_list == 1:
                return result
            
            # 현재 레벨의 노드들을 결과 리스트에 추가
            for n in thislevel:
                if n != None: 
                    result.append(n.val)
                    nextlevel.append(n.left)
                    nextlevel.append(n.right)
                else:
                    result.append(None)
                    nextlevel.append(None)
                    nextlevel.append(None)
            
            # 다음 레벨로 이동
            thislevel = nextlevel
            
        return result

# 리스트에서 이진 트리를 생성하는 함수
from collections import deque

# TreeNode로 반환
def create_linked_bst(arr: list):
    # 주어진 리스트가 비어있는 경우 None 반환
    if len(arr) < 1: return None
    
    # 리스트의 요소를 순회하는 반복자 초기화
    n = iter(arr)
    
    # 루트 노드 생성
    tree = TreeNode(next(n))
    
    # 생성된 노드를 저장하는 큐 초기화
    fringe = deque([tree])
    
    # 리스트의 모든 요소를 순회
    while True:
        # 큐에서 노드를 꺼내서 자식 노드를 추가
        head = fringe.popleft()
        
        try:
            l = next(n)
            # 왼쪽 자식 노드를 생성 (값이 None인 경우에는 노드를 생성하지 않음)
            head.left = TreeNode(l) if l != None else None
            fringe.append(head.left)
            
            r = next(n)
            # 오른쪽 자식 노드를 생성 (값이 None인 경우에는 노드를 생성하지 않음)
            head.right = TreeNode(r) if r != None else None
            fringe.append(head.right)
        except StopIteration:
            # 리스트의 모든 요소를 순회한 경우 루프 종료
            break
            
    return tree
################################################################


def P2(root:TreeNode):
    
    # 입력된 root가 없을 경우 빈 list 반환
    if not root:
        return []
    
    # 결과를 저장할 list와 BFS traversal을 위한 queue 초기화
    # 각 노드의 자식을 알아야 traversal가 가능하기 때문에 root.val이 아닌 root로 넣어야 함
    result, queue = [], [root]
    
    # queue에 node가 있을 동안 traversal
    while queue:
        cur_level = []
        level_size = len(queue)
        
        # 현재 level의 nodes 돌면서 node value 저장
        for node in range(level_size):
            cur_node = queue.pop(0)
            cur_level.append(cur_node.val)
            
            # 현재 노드에 left child node가 있으면 queue에 넣기
            if cur_node.left:
                queue.append(cur_node.left)
            # 현재 노드에 right child node가 있으면 queue에 넣기
            if cur_node.right:
                queue.append(cur_node.right)
        
        # 각 level들 담기
        result.append(cur_level)
        
    # leaf부터 root까지 왼쪽에서 오른쪽 순서이므로 reverse 필요
    result.reverse()    
    return result
    