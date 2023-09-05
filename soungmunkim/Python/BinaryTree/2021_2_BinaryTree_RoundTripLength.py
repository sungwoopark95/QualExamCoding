"""
[Tree가 주어졌을 때 가장 긴 Round trip length 구하기]
     1
    / \
   2   3    답은 4
   
      1
    /  \
   2    4
  /      \
3         5 답은 8


    1
     \
      2
     / \
    3   4
   /     \
  5       6   답은 8. 5에서 출발했다가 2까지 갔다가 6으로 갔다가 똑같이 돌아오면 됨. 꼭 Root를 거칠 필요 없음
"""

# 이진 트리의 노드를 표현하는 클래스
class BTNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val  # 노드의 값
        self.left = left  # 왼쪽 자식 노드
        self.right = right  # 오른쪽 자식 노드

# 이진 트리에서 가장 긴 원형 경로의 길이를 찾는 함수
# 최단 원형 경로의 길이를 찾고 싶으면 max 대신 min 사용

"""
single path: 한 노드에서 시작해서 right or left 경로로 한 방향 따라가는거
round path: 특정 노드에 시작해서 subtree 타고 내려간 뒤 해당 노드로 돌아와 반대 subtree로 감
    = 두 개의 single path 결합한 것
    
원형 경로의 길이를 최대화하려면 각 서브트리에서의 단일 경로의 최대 길이를 사용해야 합니다.
-> 각 노드에서 재귀적으로 단일 경로의 최대 길이를 계산하고, 이를 사용하여 원형 경로의 길이를 계산
"""

def roundTripLongestRouteOfBT(root: BTNode):
    def helper(node):
        # 현재 노드가 리프 노드인 경우
        if node.left is None and node.right is None:
            return 0, 0
            
        # 현재 노드의 왼쪽 자식 노드만 없는 경우
        if node.left is None:
            roundLen, singleLen = helper(node.right)
            return max(roundLen, singleLen + 1), singleLen + 1
        
        # 현재 노드의 오른쪽 자식 노드만 없는 경우
        if node.right is None:
            roundLen, singleLen = helper(node.left)
            return max(roundLen, singleLen + 1), singleLen + 1
        
        # 둘 다 자식 노드가 있는 경우
        l_roundLen, l_singleLen = helper(node.left)
        r_roundLen, r_singleLen = helper(node.right)
        roundLen = max(l_roundLen, r_roundLen)
        
        # 이전 roundlen or 현재 roundlen(해당 노드 두번 들려야함)중 Max 값, 두 singlelen 중 max값 + 해당노드
        return max(roundLen, l_singleLen + r_singleLen + 2), max(l_singleLen, r_singleLen) + 1

    # 함수의 결과를 반환합니다. (2를 곱하는 이유는 원형 경로이기 때문입니다.)
    return 2 * max(helper(root))
  
  

# Test Case
# 테스트 케이스를 구성하기 위한 트리 노드 생성
tree2 = BTNode(2)
tree3 = BTNode(3)
tree4 = BTNode(4)
tree6 = BTNode(6)
tree7 = BTNode(7)
tree8 = BTNode(8)
tree9 = BTNode(9)
tree10 = BTNode(10)

# 트리 구조를 구성합니다.
tree4.left = tree2
tree4.right = tree6
tree2.right = tree3
tree6.right = tree7
tree6.left = tree8
tree8.left = tree9
tree9.right = tree10

# 함수를 호출하여 결과를 출력합니다.
print(roundTripLongestRouteOfBT(tree4)) #12

# 또 다른 테스트 케이스를 구성하기 위한 트리 노드 생성
tree2 = BTNode(2)
tree3 = BTNode(3)
tree6 = BTNode(6)
tree7 = BTNode(7)
tree9 = BTNode(9)
tree10 = BTNode(10)

# 트리 구조를 구성합니다.
tree9.right = tree6
tree6.left = tree3
tree6.right = tree7
tree3.left = tree2
tree7.left = tree10

# 함수를 호출하여 결과를 출력합니다.
print(roundTripLongestRouteOfBT(tree9)) #8
