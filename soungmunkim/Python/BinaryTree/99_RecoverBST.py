"""
[binary tree를 bst로 만들기]

Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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

################# 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 (null 프린트 안 하는 버전) ##################
def print_BST(node:TreeNode):
    if not node:              # 노드가 없으면 빈 리스트 반환
        return []

    result = []
    queue = [node]            # 초기 큐에 루트 노드 저장

    while queue:              # 큐가 빌 때까지 반복
        current = queue.pop(0) # 큐에서 노드 꺼내기
     
        result.append(current.val)  # 결과 리스트에 키 값 추가

        if current.left:      # 왼쪽 자식이 있으면 큐에 추가
            queue.append(current.left)
        if current.right:     # 오른쪽 자식이 있으면 큐에 추가
            queue.append(current.right)

    return result             # 결과 리스트 반환



################# 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 ##################
def print_BST_withNull(node: TreeNode):
    result = []
    queue = [node]  # 초기 큐에 루트 노드 저장

    while queue:  # 큐가 빌 때까지 반복
        current = queue.pop(0)  # 큐에서 노드 꺼내기
        
        # 노드가 없을 경우 "null" 추가, 있을 경우 값 추가
        if current:
            result.append(current.val)
            # null이 아닐 때만 자식 노드들을 큐에 추가
            if current.left or current.right: 
                queue.append(current.left)  # 왼쪽 자식을 큐에 추가
                queue.append(current.right)  # 오른쪽 자식을 큐에 추가
        else:
            result.append("null")

        # # 노드가 없을 경우 "null" 추가, 있을 경우 값 추가
        # if current:
        #     result.append(current.val)
        #     queue.append(current.left)  # 왼쪽 자식을 큐에 추가 (노드가 없어도 "null" 처리를 위해 추가)
        #     queue.append(current.right)  # 오른쪽 자식을 큐에 추가 (노드가 없어도 "null" 처리를 위해 추가)
        # else:
        #     result.append("null")

    print(result)  # 결과 리스트 출력




################# inorder로 list에 넣는 함수 ##################
# 중위 순회를 통해 노드의 값을 순서대로 반환하는 함수
def inorder_traversal(node):
    result = []

    # 주어진 노드의 값을 중위 순서로 result에 추가하는 내부 함수
    def inorder(n):
        if n:  # 현재 노드가 None이 아닐 때만 처리
            inorder(n.left)  # 왼쪽 서브 트리를 중위 순회
            result.append(n.val)  # 현재 노드의 값을 결과 리스트에 추가
            inorder(n.right)  # 오른쪽 서브 트리를 중위 순회

    inorder(node)
    return result

################# inorder로 저장된 list를 bst로 변환하는 함수 (sorted 필수!) ##################
# 중위 순회를 통해 주어진 트리를 BST로 변환하는 함수
def inorder_to_bst(node, vals):
    if not node:  # 현재 노드가 None이면 vals를 그대로 반환
        return vals

    vals = inorder_to_bst(node.left, vals)  # 왼쪽 서브 트리를 BST로 변환
    node.val = vals.pop(0)  # vals에서 첫 번째 값을 꺼내 현재 노드의 값으로 설정
    vals = inorder_to_bst(node.right, vals)  # 오른쪽 서브 트리를 BST로 변환

    return vals

# 주어진 이진 트리를 BST로 변환하는 함수
def bstify(root: list) -> TreeNode:
    tree = list_to_btree(root)
    vals = sorted(inorder_traversal(tree))  # 트리의 값을 중위 순서로 정렬
    inorder_to_bst(tree, vals)  # 정렬된 값을 이용하여 트리를 BST로 변환

    return print_BST_withNull(tree)  # 변환된 BST의 루트 노드 반환


if __name__ == '__main__':
    root = [1,3,None,None,2]
    bstify(root)