from CreateBST import TreeNode, create_linked_bst

def P3(root: TreeNode, val: int):    
    ##### Write your Code Here #####

    def __balancedBST(nodes: list, start: int, end: int):
        """
        1. 중앙 노드 선택: 주어진 정렬된 노드 리스트에서 중앙에 위치한 노드를 선택합니다. 이 노드가 현재 서브트리의 루트 노드가 됩니다. 
           중앙 노드는 (start + end) // 2로 계산됩니다.
        2. 왼쪽 서브트리 생성: 중앙 노드의 왼쪽에 있는 노드들을 이용하여 왼쪽 서브트리를 생성합니다. 
           이를 위해 __balancedBST 함수를 재귀적으로 호출하며, start부터 mid-1까지의 노드들을 사용합니다.
        3. 오른쪽 서브트리 생성: 중앙 노드의 오른쪽에 있는 노드들을 이용하여 오른쪽 서브트리를 생성합니다. 
           이를 위해 __balancedBST 함수를 재귀적으로 호출하며, mid+1부터 end까지의 노드들을 사용합니다.
        4. 서브트리 연결: 중앙 노드의 left 포인터를 왼쪽 서브트리의 루트로, right 포인터를 오른쪽 서브트리의 루트로 설정합니다.
        5. 루트 반환: 현재 서브트리의 루트 노드를 반환합니다.
        이 원리를 기반으로, 함수는 주어진 정렬된 노드 리스트를 이용하여 균형잡힌 이진 탐색 트리를 생성합니다. 중앙 노드를 루트로 선택하는 것은 BST의 특성을 유지하기 위함입니다. 중앙 노드를 기준으로 왼쪽에는 더 작은 값들, 오른쪽에는 더 큰 값들이 위치하게 되므로, 이를 이용하여 재귀적으로 균형잡힌 BST를 구성하게 됩니다.
        """
        if start > end:
            return None

        mid = (start + end) // 2
        node = nodes[mid]

        node.left = __balancedBST(nodes, start, mid-1)
        node.right = __balancedBST(nodes, mid+1, end)

        return node
    
    def __insertBST(root: TreeNode, val: int):
        """
        1. 기본 케이스: 만약 현재 루트(root)가 None이면, 새로운 노드를 생성하고 그 값을 반환합니다.
        2. 재귀 케이스: 현재 루트의 값이 삽입하려는 값보다 작다면, 오른쪽 서브트리에 값을 삽입해야 합니다. 
           그렇지 않다면 왼쪽 서브트리에 삽입합니다. 이를 위해 해당 서브트리의 루트를 대상으로 __insertBST 함수를 재귀적으로 호출합니다.
        3. 마지막으로, 현재 루트를 반환합니다. 이는 현재 노드 아래의 서브트리에 변화가 있을 수 있기 때문입니다.
        """
        if root == None:
            return TreeNode(val)

        else:
            if root.val < val:
                root.right = __insertBST(root.right, val)
            else:
                root.left = __insertBST(root.left, val)

        return root

    def __storeBST(root: TreeNode, nodes: list):
        """
        이 함수는 주어진 BST의 모든 노드를 중위 순회 방식으로 방문하며, 노드들을 주어진 리스트(nodes)에 추가하는 재귀 함수입니다.
        원리:
        1. 중위 순회: BST의 중위 순회는 노드들을 오름차순으로 방문합니다. 
           따라서, __storeBST 함수는 먼저 왼쪽 서브트리를 방문, 그 다음 현재 노드를 리스트에 추가, 
           그리고 오른쪽 서브트리를 방문하는 순서로 작동합니다.
        2. 이 방식으로, nodes 리스트는 BST의 모든 노드를 오름차순으로 포함하게 됩니다.
        """
        if root == None:
            return
        __storeBST(root.left, nodes)
        nodes.append(root)
        __storeBST(root.right, nodes)

    root = __insertBST(root, val)
    nodes = []
    __storeBST(root, nodes)
    
    n = len(nodes)
    print([node.val for node in nodes])
    return __balancedBST(nodes, 0, n-1)
    ##### End of your code #####
    
if __name__ == "__main__":
    root = create_linked_bst([7,3,8,2,5,None,9]) 
    fullBST = P3(root, 6) 
    fullBST.printTree()
