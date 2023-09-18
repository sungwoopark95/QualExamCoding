"""
[제일 깊은 leaves의 합 구하기]

root = [1,2,3,4,5,None,6,7,None,None,None,None,8]
tree = list_to_btree(root)
deepestLeavesSum(tree)
paths:  [[1, 2, 4, 7], [1, 2, 5], [1, 3, 6, 8]]
15

root = [6,7,8,2,7,1,3,9,None,1,4,None,None,None,5]
tree = list_to_btree(root)
deepestLeavesSum(tree)
paths:  [[1, 2, 4, 7], [1, 2, 5], [1, 3, 6, 8]]
15
paths:  [[6, 7, 2, 9], [6, 7, 7, 1], [6, 7, 7, 4], [6, 8, 1], [6, 8, 3, 5]]
19
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

# binary tree root -> leaf 각 paths 찾아주는 함수 
# bst에서도 사용 가능
def findPaths(root, current_path, paths):
    if not root:
        return

    # 현재 경로에 노드 값을 추가
    current_path.append(root.val)

    # 리프 노드에 도달하면 현재 경로를 결과에 추가
    if not root.left and not root.right:
        paths.append(list(current_path))
    else:
        findPaths(root.left, current_path, paths)
        findPaths(root.right, current_path, paths)

    # 백트래킹: 현재 노드를 방문을 마치고 부모 노드로 돌아가기 위해 경로에서 제거
    current_path.pop()

def deepestLeavesSum(root:TreeNode):
    # find all binary tree paths
    paths = []
    
    findPaths(root, [], paths)
    print("paths: ", paths)
    
    # max length가 먼지 첮기
    max_path = -1
    for i in range(len(paths)):
        if len(paths[i]) > max_path:
            max_path = len(paths[i])
            
    # max length 중 마지막 요소들만 sum에 더하기
    sum = 0
    for i in range(len(paths)):
        if len(paths[i]) == max_path:
            sum += paths[i][-1]
    
    return sum
    
    
    
    
# ----------------------- BFS로 푼 방식 -------------------------#
# int deepestLeavesSum(TreeNode* root) {
#     // root가 null이면, 0을 반환합니다.
#     if(!root) return 0;

#     // BFS를 위한 큐를 생성합니다.
#     std::queue<TreeNode*> q;
#     // root 노드를 큐에 넣습니다.
#     q.push(root);

#     int sum = 0;  // 각 레벨의 합을 저장하기 위한 변수

#     // 큐가 빌 때까지 반복합니다.
#     while(!q.empty()) {
#         sum = 0;  // 매 레벨마다 합을 리셋합니다.
#         int size = q.size();  // 현재 레벨의 노드 개수

#         // 현재 레벨의 모든 노드를 처리합니다.
#         for(int i = 0; i < size; i++) {
#             TreeNode* current = q.front(); q.pop();  // 큐의 맨 앞 노드를 꺼냅니다.
#             sum += current->val;  // 현재 노드의 값을 합에 추가합니다.

#             // 왼쪽 자식 노드가 있으면 큐에 추가합니다.
#             if(current->left) q.push(current->left);
#             // 오른쪽 자식 노드가 있으면 큐에 추가합니다.
#             if(current->right) q.push(current->right);
#         }
#     }

#     // 가장 깊은 레벨의 합을 반환합니다.
#     return sum;
# }