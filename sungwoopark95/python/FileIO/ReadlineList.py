"""
# P2

임의의 txt파일이 주어질 때, 해당 파일을 읽어와 각 행을 반대 순서로 리스트에 저장하고 해당 리스트를 return하는 함수를 작성하여라.
"""

def P2(fname:str):
    with open(fname, 'r') as f:
        lines = f.readlines()
    lines.reverse()
    return lines

if __name__ == "__main__":
    print(P2('alkaline_metals.txt'))
