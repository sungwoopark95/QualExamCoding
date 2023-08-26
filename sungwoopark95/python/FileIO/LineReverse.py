"""
# P1

주어진 alkaline_metals.txt의 파일을 불러오고, list of lists 형태로 파일의 내용을 return하는 함수를 작성하여라. 

단, 아래 조건을 만족한다.  

(1) 각 Inner list는 각 행을 [원자이름, 원자번호, 원자량] 형태로 저장한다. 

(2) (1)에서 만든 모든 리스트를 원소로 갖는 list of lists가 P1 함수의 최종 return값이 된다.  
"""

def P1(fname:str):
    with open(fname, 'r') as f:
        lines = f.readlines() # line들을 list 형태로 저장
    for i, item in enumerate(lines):
        lines[i] = item.strip().split(' ')
    return lines

if __name__ == "__main__":
    print(P1('alkaline_metals.txt'))
