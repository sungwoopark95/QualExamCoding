"""
[Balanced BST 만들기]
"""

# TreeNode 클래스: 이진 트리의 노드를 표현하기 위한 클래스
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val  # 노드의 값
        self.left = left  # 왼쪽 자식 노드를 가리키는 포인터
        self.right = right  # 오른쪽 자식 노드를 가리키는 포인터

# 중위 순회 함수: 주어진 노드를 시작으로 중위 순회를 하며 결과를 리스트에 저장
def inorder_traversal(node, result):
    if not node:
        return
    inorder_traversal(node.left, result)  # 왼쪽 서브트리 순회
    result.append(node.val)  # 현재 노드의 값을 리스트에 추가
    inorder_traversal(node.right, result)  # 오른쪽 서브트리 순회

# 정렬된 리스트로부터 높이 균형 BST 생성 함수
def sorted_list_to_BST(nums):
    if not nums:
        return None

    mid = len(nums) // 2  # 리스트의 중앙 인덱스 계산

    # 중앙 인덱스 값을 가진 노드를 루트 노드로 생성
    root = TreeNode(nums[mid])
    # 중앙 인덱스 왼쪽의 리스트를 사용하여 왼쪽 서브트리 생성
    root.left = sorted_list_to_BST(nums[:mid])
    # 중앙 인덱스 오른쪽의 리스트를 사용하여 오른쪽 서브트리 생성
    root.right = sorted_list_to_BST(nums[mid+1:])

    return root  # 생성된 서브트리의 루트 노드 반환

# 주어진 이진 트리를 높이 균형 BST로 변환하는 함수
def convert_to_BST(root):
    # 중위 순회를 통해 트리의 모든 값을 리스트에 저장
    values = []
    inorder_traversal(root, values)
    values.sort()  # 리스트 정렬

    # 정렬된 리스트를 이용해 높이 균형 BST 구성 후 반환
    return sorted_list_to_BST(values)

# 예제 이진 트리 생성
root = TreeNode(10)
root.left = TreeNode(5)
root.right = TreeNode(15)
root.left.left = TreeNode(3)
root.left.right = TreeNode(7)
root.right.right = TreeNode(18)

# 높이 균형 BST로 변환
new_root = convert_to_BST(root)

# 변환된 BST 확인을 위한 중위 순회 출력 함수
def print_inorder(node):
    if not node:
        return
    print_inorder(node.left)  # 왼쪽 서브트리 순회
    print(node.val, end=" ")  # 현재 노드의 값 출력
    print_inorder(node.right)  # 오른쪽 서브트리 순회

print("Converted Height Balanced BST (Inorder):")
print_inorder(new_root)
