"""
# P5

임의의 txt 파일이 주어질 때, 해당 파일에서 가장 긴 단어의 길이(int)를 return하는 함수를 작성하여라.  

※ 단어는 공백(‘ ’) 또는 개행문자(\n)로 구분된다. 

※ ‘ ‘, ‘\n’ 이외의 white space 문자는 존재하지 않는다. (ex. ‘ ‘, ‘ ‘, ‘\t’ 등)  ※ 파일에는 적어도 한 개의 단어가 있으며, 숫자는 존재하지 않는다. (한글 혹은 영어만 존재함) 
"""

def P5(fname:str):
    with open(fname, 'r') as f:
        lines = [line.strip() for line in f.readlines()]
    maxlen = -1
    for line in lines:
        for item in line.split(' '):
            if maxlen < len(item):
                maxlen = len(item)
    return maxlen

if __name__ == "__main__":
    print(P5('alkaline_metals.txt'))
