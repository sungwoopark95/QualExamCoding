"""
[binary tree의 오른쪽 side node만 프린트하기]

Given the root of a binary tree, imagine yourself standing on the right side of it, 
return the values of the nodes you can see ordered from top to bottom.

root = [1,2,3,None,5,None,4]
tree = list_to_btree(root)
rightSideView(tree)
[1, 3, 4]

root = [1,None,3]
tree1 = list_to_btree(root)
rightSideView(tree1)
[1, 3

root = []
tree2 = list_to_btree(root)
rightSideView(tree2)]
[]
"""

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 숫자 리스트를 이진 트리로 변환하는 함수
def list_to_btree(nums: list) -> TreeNode:
    if not nums:
        return None

    # 노드들을 저장할 큐를 생성합니다.
    queue = []
    
    # 루트 노드를 생성하고 큐에 추가합니다.
    root = TreeNode(nums[0])
    queue.append(root)
    
    # 노드들을 연결하기 위해 리스트를 순회합니다.
    i = 1
    while queue and i < len(nums):
        # 현재 노드를 큐에서 꺼냅니다.
        current = queue.pop(0)
        
        # 왼쪽 자식이 있다면, 연결하고 큐에 추가합니다.
        if nums[i] is not None:
            left_child = TreeNode(nums[i])
            current.left = left_child
            queue.append(left_child)
        i += 1

        # 오른쪽 자식이 있다면, 연결하고 큐에 추가합니다.
        if i < len(nums) and nums[i] is not None:
            right_child = TreeNode(nums[i])
            current.right = right_child
            queue.append(right_child)
        i += 1

    return root

def rightSideView(root:TreeNode):
    if not root:
        return []
    
    q=[root] #root는 treenode이기 대문에 root노드 하나만 들어감 (초기화)
    ans =[]
    # queue가 빌때까지 둘기
    while q:
        for i in range(len(q)): #bfs로 돌기 right는 맨 마지막에 넣고 left부터 꺼내는 방식
            a=q.pop(0)
            if a.left:
                q.append(a.left)
            if a.right:
                q.append(a.right) 
        # 왼쪽 먼저 넣고 왼쪽 먼저 빼는 방식이니까 맨 마지막 빼는 건 항상 right side 쪽
        ans.append(a.val)
    return ans

if __name__ == "__main__":
    root = [1,2,3,None,5,None,4]
    tree = list_to_btree(root)
    result = rightSideView(tree)
    print(result)  # 결과 출력