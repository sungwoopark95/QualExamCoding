"""
[subroot의 tree가 해당 root tree의 subtree인지 체크하는 함수]

root = [3,4,5,1,2]
subroot = [4,1,2]
tree= list_to_btree(root)
subtree = list_to_btree(subroot)
isSubtree(tree, subtree)
>>> True

root = [3,4,5,1,2,None, None, None,None,0]
subroot = [4,1,2]
tree = list_to_btree(root)
subtree = list_to_btree(subroot)
isSame(tree, subtree)
>>> False
"""

from collections import deque
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

#---------------------- 두 binary tree가 같은지 체크 ----------------------#
def isSame(root1: TreeNode, subRoot: TreeNode):
    # 각 queue에 root와 root pos부터 담기
    subrootQ = [(subRoot, 0)]
    rootQ = [(root1, 0)]

    while rootQ and subrootQ:
        # 각 node의 val과 해당 pos가 right, left인지 비교
        sub_cur, sub_pos = subrootQ.pop(0)
        root_cur, root_pos = rootQ.pop(0)
        # print((sub_cur.val, root_cur.val))

        # 서로 pos나 val이 다르면 false
        if sub_pos != root_pos:
            return False
        if sub_cur.val != root_cur.val:
            return False

        # 각각 다음 node와 pos 넣기
        if sub_cur.right:
            subrootQ.append((sub_cur.right, 1))
        if root_cur.right:
            rootQ.append((root_cur.right,1))
        if sub_cur.left:
            subrootQ.append((sub_cur.left,2))
        if root_cur.left:
            rootQ.append((root_cur.left,2))
    
    # 한 tree 다 돌았는데 아직 남은 tree있으면 false
    if not rootQ and not subrootQ:
        # print("here")
        return True
    
    return False
#------------------------------------------------------------------------#


def isSubtree(root: TreeNode, subRoot: TreeNode):
    q = [root]

    while q:
        cur = q.pop(0)
        # 현재 노드와 subtree root가 같다면 is same인지 체크
        if cur.val == subRoot.val:
            if (isSame(cur, subRoot)):
                return True
        if cur.right:
            q.append(cur.right)
        if cur.left:
            q.append(cur.left)
        

    return False


####################################### 시간안에 풀려고 했던 코드 (path 다 찾아서 val로만 비교한 것) #############################33
# def isSubtree(root: TreeNode, subRoot: TreeNode) -> bool:

#     def isSame(root1:TreeNode, root2: TreeNode):
#         # print(root1)
#         # print(root2)

#         allsublist1 = []
#         for sub in subtree:
#             q1 = sub
#             sublist1 = []
#             while q1:
#                 cur1 = q1.pop(0)
#                 sublist1.append(cur1.val)

#                 if cur1.left:
#                     q1.append(cur1.left)
#                 if cur1.right:
#                     q1.append(cur1.right)
#             allsublist1.append(sublist1)

#         q2 = [root2]
#         sublist2 = []

#         while q2:
#             cur2 = q2.pop(0)
#             sublist2.append(cur2.val)

#             if cur2.left:
#                 q2.append(cur2.left)
#             if cur2.right:
#                 q2.append(cur2.right)

#         print(allsublist1, sublist2)   

#         if sublist2 in allsublist1:
#             return True
#         return False


#     if not root:
#         return None
    
#     q = [root]
#     subtree = []

#     while q:
#         cur = q.pop(0)
#         # print("cur: ", cur.val, "subroot: ", subRoot.val)
#         if cur.val == subRoot.val:
#             subtree.append([cur])
            
        
#         if cur.left:
#             q.append(cur.left)

#         if cur.right:
#             q.append(cur.right)


#     return isSame(subtree, subRoot)