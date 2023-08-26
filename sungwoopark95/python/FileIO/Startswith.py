"""
# P3
임의의 txt파일이 주어질 때, 파일을 불러온 뒤 다음 조건에 맞는 list를 return하는 함수를 작성하여라. 

(1) 각 행을 읽은 순서대로 하나의 list에 추가한다. 

(2) 단, ‘#’나 ‘//’로 시작하는 행은 주석으로 취급하여 추가하지 않는다. 
"""

## startswith
def P3(fname:str):
    ans = []
    with open(fname, 'r') as f:
        line = f.readline()
        while line:
            if line.startswith('#') or line.startswith('//'):
                line = f.readline()
                continue
            ans.append(line)
            line = f.readline()
    return ans

if __name__ == "__main__":
    print(P3('alkaline_metals2.txt'))
