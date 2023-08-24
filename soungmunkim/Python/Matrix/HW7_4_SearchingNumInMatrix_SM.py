"""
[Matrix가 주어졌을 때 찾고자 하는 목표 숫자가 nested list안에 있으면 좌표를 Tuple 형태로 반환하고, 없으면 (-1, -1)을 반환]

TestCase1)
matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]
target = 3
P4(matrix, target)
(0, 1)
TestCase2)
matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]] 
target = 65
P4(matrix, target)
(-1, -1)
"""
def P4(matrix:list, target:int) -> tuple:
    dic = {}
    index1, index2 = -1, -1
    
    # 각 row마다 dic에 저장하기
    for idx, lst in enumerate(matrix):
        dic[idx] = lst
    
    # 해당 target이 해당 row에 있으면 index 뽑기
    for k,v in dic.items():
        if target in v:
            index1 = k
            index2 = v.index(target)
            
    return (index1, index2) 