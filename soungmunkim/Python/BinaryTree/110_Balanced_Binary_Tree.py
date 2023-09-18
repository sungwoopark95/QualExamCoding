"""
Binary Tree의 모든 node에 대해서, 해당 노드의 left subtree의 depth와 right subtree의 depth가 1보다 많이 차이나면 False, 1 이하로 차이나면 True
=> 모든 node에 대해 검사해야 하므로 recursion 필요!

root_list = [3,9,20,None,None,15,7]
root = list_to_btree(root_list)
print(isBalanced(root)) -> True

root_list = [1,2,2,3,3,null,null,4,4]
root = list_to_btree(root_list)
print(isBalanced(root)) -> False
"""
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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

# 함수 bfs는 주어진 노드로부터 가장 깊은 깊이(레벨)를 반환합니다.
def bfs(root):
    # 주어진 노드가 없으면 깊이 0을 반환합니다.
    if not root:
        return 0
    # BFS를 위한 큐를 초기화합니다. 각 항목은 (노드, 레벨) 쌍입니다.
    queue = [(root, 0)]
    while queue:
        # 큐에서 첫 번째 항목을 꺼냅니다.
        curr_node, curr_level = queue.pop(0)
        # 왼쪽 자식 노드가 있으면 큐에 추가합니다.
        if curr_node.left:
            queue.append((curr_node.left, curr_level+1))
        # 오른쪽 자식 노드가 있으면 큐에 추가합니다.
        if curr_node.right:
            queue.append((curr_node.right, curr_level+1))
    # 마지막으로 방문한 노드의 깊이+1을 반환합니다.
    return curr_level+1

def isBalanced(root: TreeNode) -> bool:
    # 함수 is_balanced는 주어진 노드의 서브트리가 균형 잡혔는지 판단합니다.
    def is_balanced(root):
        # 주어진 노드가 없으면 True를 반환합니다.
        if not root:
            return True
        
        # 왼쪽과 오른쪽 서브트리의 깊이를 계산합니다.
        left_depth = bfs(root.left)
        right_depth = bfs(root.right)
        
        # 두 서브트리의 깊이 차이가 1보다 크면 False를 반환합니다.
        if abs(left_depth - right_depth) > 1:
            return False
        
        # 현재 노드의 서브트리가 균형 잡혔다면, 왼쪽과 오른쪽 자식 노드에 대해 같은 테스트를 수행합니다.
        return is_balanced(root.left) and is_balanced(root.right)

    # 트리의 루트 노드에서 시작하여 전체 트리가 균형 잡혔는지 판단합니다.
    return is_balanced(root)


if __name__ == "__main__":
    root_list = [3,9,20,None,None,15,7]
    root = list_to_btree(root_list)
    print(isBalanced(root))
