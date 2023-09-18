"""
주어진 이진 탐색 트리(BST)에서 두 주어진 노드의 최소 공통 조상(LCA) 노드를 찾아라.

"최소 공통 조상은 두 노드 p와 q에 대하여 p와 q 모두를 후손으로 갖는 T의 가장 낮은 노드로 정의된다. 
(이때, 노드가 자신의 후손이 될 수 있음을 허용한다.)"

root = [6,2,8,0,4,7,9,None,None,3,5]
p = 2
q = 8
tree = list_to_btree(root)
lowestCommonAncestor(tree, p, q) # 6


root = [6,2,8,0,4,7,9,None,None,3,5]
p = 2
q = 4
tree1 = list_to_btree(root)
lowestCommonAncestor(tree1, p, q) # 2
"""


class TreeNode:
    # 초기화 함수로 노드 값을 설정하고 왼쪽, 오른쪽 자식 노드를 초기화합니다.
    def __init__(self, val=0, left=None, right=None):
        self.val = val       # 노드의 값을 저장하는 변수
        self.left = left     # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right   # 오른쪽 자식 노드를 가리키는 포인터

# 숫자 리스트를 이진 트리로 변환하는 함수
def list_to_btree(nums: list):
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

def lowestCommonAncestor(root:TreeNode, p: int, q: int) -> TreeNode:
    # p, q 중에서 가장 큰 값을 largest, 가장 작은 값을 smallest에
    smallest = min(p, q)
    largest = max(p, q)
    
    while root:
        # 가장 작은 값이 현재 노드 값보다 크면 right subtree로
        if smallest > root.val:
            root = root.right
        # 가장 큰 값이 현재 노드 값보다 작으면 left subtree로
        elif largest < root.val:
            root = root.left
        # 그렇지 않으면 
        #(즉, smallest는 현재 노드의 값보다 작거나 같고 
        # largest는 현재 노드의 값보다 크거나 같은 경우)
        # LCA 임으로 해당 값 출력
        else:
            return root.val
