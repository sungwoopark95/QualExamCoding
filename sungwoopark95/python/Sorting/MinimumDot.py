"""
서로 다른 두 List에 대해서, 내적을 최소화하는 함수
"""

from typing import List

## inner product를 최소화하는 방법 -> 하나의 vector는 ascending order, 다른 vector는 descending order로 정렬한 뒤 수행
def P5(A:List[int], B:List[int]):
    def inner_product(list1, list2):
        val = 0
        for item, jtem in zip(list1, list2):
            val += (item * jtem)
        return val
    
    # 한 번은 A를 ascending, B를 descending, 한 번은 B를 ascending, A를 descending -> 둘 중에 작은 값
    candidate1 = inner_product(sorted(A), sorted(B, reverse=True))
    candidate2 = inner_product(sorted(A, reverse=True), sorted(B))
    return min(candidate1, candidate2)

if __name__ == "__main__":
    print(P5([1,1,1,6,0], [2,7,8,3,1]))
