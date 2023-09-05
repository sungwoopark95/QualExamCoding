"""
숫자 리스트가 주어지면 그걸 그냥 binary tree로 변환하는 코드
"""

# TreeNode 클래스를 정의합니다.
class TreeNode:
    # 초기화 함수로 노드 값을 설정하고 왼쪽, 오른쪽 자식 노드를 초기화합니다.
    def __init__(self, val=0, left=None, right=None):
        self.val = val       # 노드의 값을 저장하는 변수
        self.left = left     # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right   # 오른쪽 자식 노드를 가리키는 포인터

############## 완벽한 list 형태 (꽉 찬 형태)가 아니어도 binary tree로 구현 가능 ####################
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


############## 완벽한 list 형태 (꽉 찬 형태)여야 binary tree로 구현 가능 ####################
# # 숫자 리스트를 이진 트리로 변환하는 함수
# def list_to_btree(nums):
#     # 리스트가 비어 있으면 None을 반환
#     if not nums:
#         return None

#     # nums 리스트의 각 숫자를 노드로 변환합니다. None 값이면 노드를 생성하지 않습니다.
#     nodes = []
#     for num in nums:
#         if num is not None:
#             node = TreeNode(num)
#         else:
#             node = None
#         nodes.append(node)


#     # 자식 노드들을 거꾸로 저장한 새로운 리스트를 생성합니다.
#     children_nodes = nodes[::-1]

#     # 루트 노드를 가져옵니다.
#     root = children_nodes.pop()

#     # 모든 노드에 대해서
#     for node in nodes:
#         # 노드가 None이 아니라면
#         if node:
#             # 남아있는 자식 노드들 중에서 왼쪽 자식을 설정합니다.
#             if children_nodes: node.left = children_nodes.pop()
#             # 남아있는 자식 노드들 중에서 오른쪽 자식을 설정합니다.
#             if children_nodes: node.right = children_nodes.pop()

#     # 변환된 루트 노드를 반환합니다.
#     return root