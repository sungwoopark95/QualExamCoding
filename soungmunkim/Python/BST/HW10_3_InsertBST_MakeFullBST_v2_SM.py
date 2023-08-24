"""
[Insert value into BST -> Make full BST]
Full BST 에서 1 개의 Node 만 비어 있는 BST 에 1 개의 값을 추가하여 Full BST 로 만들고, root node 를 return 하는 함수를 작성하여라.

• Input 은 BST 의 root node 와 추가할 정수값이다.
• Node 의 모든 값은 정수라고 가정한다.
• 추가되는 값은 Input BST 에 존재하지 않는다고 가정한다.
 
• Tree 를 새로 생성하는 방식으로의 구현은 인정하지 않는다. 
(ex. 원래 tree 의 값들을 받아 리스트로 만든 뒤 다음 값을 추가해서 create_linked_bst 를 사용하는 방식의 구현은 안됨)

>>> root = create_linked_bst( [7,3,8,2,5,None,9])
>>> fullBST = P3(root, 6)
>>> print(fullBST .printTree())
[6, 3, 8, 2, 5, 7, 9]
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

# TreeNode로 반환됨
def P3(root:TreeNode, val:int):
    
    """ 
    countNode 함수 (노드 개수 파악): 
    subtree의 left와 right child의 노드 개수 파악
    어느 subtree에 값을 insert할지 결정할 때 쓰임
    """
    def countNode(head):
        # base case
        if head is None:
            return 0
        return 1 + countNode(head.right) + countNode(head.left) # root + right subtree node 개수 + left subtree node 개수
    
    """
    help function:
    주어진 subtree에 값을 insert하고, 새로운 subtree를 return 하는 recursive function
    """
    def _insert(head, val):
        # base case
        if head is None:
            # 새로운 val 값을 가진 TreeNode 생성하고 return함
            return TreeNode(val)
        # head가 None이 아니면 head의 left와 right subtree의 node 수를 세고 head 값을 root val로 둠
        left_cnt = countNode(head.left) # 해당 node의 left subtree node 개수
        right_cnt = countNode(head.right) # 해당 node의 right subtree node 개수
        root_val = head.val # 해당 값을 root val로 둠
        
        """
        left나 right child 중 하나가 None 일 경우 
        (left subtree가 없거나 right subtree가 없는 경우) -> 새 value를 적절한 위치에 insert하고 return함
        """
        # left가 None 일 경우 (left subtree가 없는 경우)
        if left_cnt == 0:
            right_val = head.right.val # head의 right node의 val
            # 만약 insert val이 head의 right node val보다 클 경우) head.left: 기존 root val / head: head.right val / head.right val: insert된 val 
            if val > right_val:
                head.left = TreeNode(root_val)
                head.val = right_val
                head.right.val = val
            # 만약 insert val이 root val 보다는 크고 head.right val보다는 작은 경우) head.left: 기존 root val / head: insert된 val
            elif val > root_val:
                head.left = TreeNode(root_val)
                head.val = val
            # 만약 insert val이 root val보다 작은 경우) head.left: insert된 val
            else:
                head.left = TreeNode(val)
            
            return head
        
        # right가 None 일 경우 (right subtree가 없는 경우)
        elif right_cnt == 0:
            left_val = head.left.val
            if val > root_val:
                head.right = TreeNode(val)
            elif val > left_val:
                head.right = TreeNode(root_val)
                head.val = val
            else:
                head.right = TreeNode(root_val)
                head.val = left_val
                head.left.val = val
                
            return head
        """
        left subtree에 더 많은 수의 노드가 있으면 (left subtree가 full BST라면),
        right subtree에 값을 삽입해야 함
        반대의 경우에는 반대로
        """
        # left subtree가 full일 경우 
        if left_cnt > right_cnt:
            if val > root_val: # inset val이 root val보다 크면 -> 그냥 head.right에 넣기
                head.right = _insert(head.right, val)
            # left subtree가 full인데 val이 root val보다 작을 때 -> full에  값 넣어야 함
            else:
                # left subtree에서 가장 큰 값 찾기
                parentOfLargest = head.left
                largest = head.left
                # 큰 값의 오른쪽이 없을때까지 반복 (가장 큰 값 찾을때까지)
                while largest.right is not None:
                    parentOfLargest = largest
                    largest = largest.right
                    
                # 만약 val 이 left subtree에서 가장 큰 값보다 작은 경우 
                # -> head: left subtree에서 가장 큰 값 / head.left: insert val/ head.right: 기존 root val 
                if val < largest.val:
                    head.val = largest.val
                    parentOfLargest.right = None
                    head.left = _insert(head.left, val)
                    head.right = _insert(head.right, root_val)
                
                # 만약 val이 left subtree에서 가장 큰 값보다 큰 경우
                # -> head: insert val / head.right: 기존 root val 
                else:
                    head.val = val
                    head.right = _insert(head.right, root_val)
        
        # right subtree가 full인 경우 
        else:
            # val이 root 값보다 크다면 (left subtree에 값 넣어야 함) 
            # -> right subtree에서 가장 작은 value 찾기
            if val > root_val:
                parentOfSmallest = head.right
                smallest = head.right
                # 가장 작은 값 찾을때까지 반복
                while smallest.left is not None:
                    parentofSmallest = smallest
                    smallest = smallest.left
                
                # 만약 val이 riught subtree에서 가장 작은 값보다 큰 경우
                # -> head: right subtree에서 가장 작은 값 / head.left: 기존 root val / head.right: insert val   
                if val > smallest.val:
                    head.val = smallest.val
                    parentOfSmallest.left = None
                    head.right = _insert(head.right, val)
                    head.left = _insert(head.left, root_val)
                
                # 만약 val이 right subtree에서 가장 작은 값보다 작은 경우
                # -> head: insert val / head.left: 기존 root val
                else:
                    head.val = val
                    head.left = _insert(head.left, root_val)
            # right subtree가 full인데 val이 root 값보다 작다면 -> 그냥 left subtree에 넣기         
            else:
                head.left = _insert(head.left, val)
        return head
    
    # 적절한 subtree에 값을 삽입하기 위해 recursively call 함
    _insert(root, val)
    return root
