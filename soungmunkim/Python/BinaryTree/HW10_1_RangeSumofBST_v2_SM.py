"""
[Range sum of BST]
Binary Search Tree에서 range[low, high]에 해당하는 BST의 모든 노드 값을 합산하여 반환하는 함수 작성
• BST 의 각 Node 는 TreeNode class 로 정의되며, printTree() Method 를 호출하면 tree 의 각 노드의 값을 리스트로 만들어 Return 해준다.
• Input 은 BST 의 Root Node 와 low, high 가 주어질 것이다.
• 모든 node 의 값은 BST 안에서 유일하다.

• create_linked_bst: 정수 List를 입력 받아 BST를 구성하고 root node를 반환. (BFT의 순서로 입력되어야 함 = 첫 element:root node 값)
• child node의 경우는 해당 노드의 값 보다 크거나 작아야 하지만 grand children 부터는 이 조건에 구애를 받지 않는다. 
    10 
    /\  
   5  15 
  /\  /\
 3  7 9 18
 
TestCase1) 3,5,7이 해당 range 안에 있으므로 15가 return된다.
9는 Range 안에 있으나 BST를 검색할 때 range 의 최대값 9 가 Root node 보다 작으므로 왼쪽 Subtree 만 검색하여 3,5,7 의 합만 Return 하여야 한다.
>>> root = create_linked_bst([10,5,15,3,7, 9, 18]) 
>>> P1(root, 3, 9)
15

TestCase2) 3, 5, 7, 9, 10, 15 가 해당 range 안에 있으므로 49 가 return 된다. 
range 의 최대값 15 가 Root node 보다 크므로 왼쪽, 오른쪽 Subtree 를 모두 검색하여야 하고 9 는 합산시 포함되어야 한다.
>>> root = create_linked_bst([10,5,15,3,7, 9, 18]) 
>>> P1(root, 3, 15)
49

TestCase3) 7,10,15가 해당 range 안에 있으므로 32가 return된다.
>>> root = create_linked_bst([10,5,15,3,7,None,18]) 
>>> P1(root, 7, 15)
32
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

def P1(root: TreeNode, low: int, high: int):
    	
	ans = 0
	if root == None:
		return 0
	else:
		# if root.val가 주어진 범위 안에 있을 때
		if low <= root.val <= high:
			# root value와 left, right subtree에서 범위 안에 있는 값 누적하여 합하기
			ans += root.val + P1(root.left, low, high) + P1(root.right, low, high)
		
		# root.val가 low보다 작을 때
		elif root.val < low:
			# right subtree에서 범위 내에 속하는 값들 합치기
			ans += P1(root.right, low, high)
		# root.val가 high보다 클 때
		else:
			# left subtree에서 범위 내에 속하는 값들 합하기
			ans += P1(root.left, low, high)
		
	return ans
    ##### End of your code #####