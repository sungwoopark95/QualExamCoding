from ListToBST import TreeNode, create_linked_bst

# 값 자체를 계속해서 더하기
def P1(root:TreeNode, low:int, high:int) -> int:
    ans = 0
    if root is None:
        return 0
    if low <= root.val <= high:
        ans = root.val
        print(ans)
    if root.val >= low:
        ans += P1(root.left, low, high)
    if root.val <= high:
        ans += P1(root.right, low, high)
    return ans

# 모든 값을 list에 받고, 해당 list의 sum을 return
def P1_(root:TreeNode, low:int, high:int) -> int:
    values = [] # recursion과 무관한 값이므로 새로운 함수가 필요
    
    def dft(root:TreeNode):
        if root is None:
            return
        if low <= root.val <= high:
            values.append(root.val)
        if root.val >= low:
            dft(root.left)
        if root.val <= high:
            dft(root.right)
    
    dft(root)
    
    return sum(values)

if __name__ == "__main__":
    root = create_linked_bst([10,5,15,3,7,None,18])
    print(P1(root, 7, 15))
