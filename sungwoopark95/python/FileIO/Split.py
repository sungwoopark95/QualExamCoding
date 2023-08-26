"""
# P4

임의의 txt파일이 주어질 때, 파일을 불러온 뒤 다음 조건에 맞는 list를 return하는 함수를 작성하여라. 

(1) 각 행을 읽은 순서대로 하나의 list에 추가한다. 

(2) 단, ‘#’나 ‘//’ 뒤의 문자들은 주석으로 취급하여 추가하지 않는다. 

(3) 각 행의 맨 앞과 맨 뒤, 즉 양 끝에 있는 white space 문자는 삭제한다.  주어진 alkaline_metals2.txt 파일을 활용한 예시는 다음과 같다. 
"""

## readlines
def P4(fname:str):
    with open(fname, 'r') as f:
        lines = f.readlines()
    ans = []
    for line in lines:
        line = line.strip()
        if '#' in line:
            line = line.split('#')[0].strip()
        if '//' in line:
            line = line.split('//')[0].strip()
        if len(line) > 0:
            ans.append(line)
    return ans

if __name__ == "__main__":
    print(P4('alkaline_metals2.txt'))
