"""
정렬되어 있는 2차원 List가 주어졌을 때 찾고자 하는 목표 숫자가 List안에 있으면 좌표를 Tuple 형태로 반환하고, 없으면 (-1, -1)을 반환하는 함수 `P4`를 작성하여라. 

* 2차원 List의 각 원소는 정수로 주어진다. 
* 2차원 List의 각 행은 왼쪽부터 오른쪽으로 정렬되어 있다. 
* 각 행의 첫번째 원소는 그 이전행의 마지막 원소보다 크다. 
* 입력으로 주어지는 2차원 List 안에 중복되는 값은 없다. 
* 2차원 List의 행, 열의 수는 100을 넘지 않는다. 
* 2차원 List의 모든 행은 같은 수의 원소를 갖는다. 
* 구현에 따라 작동 시간에 많은 차이가 발생할 수 있습니다. 최대한 효율적인 방식으로 문제를 해결해 보세요. 
"""

from typing import List

def P4(matrix:List[List], target:int):
    x, y = -1, -1
    for i, row in enumerate(matrix):
        if target in row:
            x = i
            y = row.index(target)
    return (x, y)

if __name__ == "__main__":
    matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]] 
    target = 3 
    print(P4(matrix, target))
