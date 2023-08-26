"""
# P6

임의의 txt 파일이 주어질 때, 주어진 파일과 다른 구분자를 갖는 텍스트 파일을 새롭게 생성하는 함수를 작성하여라. 단, 다음과 같은 조건을 만족한다. 

(1) input 파일의 구분자는 공백문자이다. (‘ ‘)  

(2) output 파일의 구분자는 콤마이다. (‘,’) 

(3) output 파일의 구분자 (콤마) 앞, 뒤로 공백은 없다. 

(4) input 파일에는 연속적인 공백문자는 등장하지 않는다. (ex. ‘ ‘, ‘ ‘, ‘ ‘ 등) 

(5) 함수의 return 값은 없다.  

주어진 alkaline_metals.txt를 input 파일로 활용한 output.txt 파일의 예시는 과제 폴더에 함께 첨부되어 있다. 
"""

def P6(in_fname:str, out_fname:str):
    with open(in_fname, 'r') as infile:
        lines = [line.strip() for line in infile.readlines()]
    with open(out_fname, 'w') as outfile:
        for line in lines:
            outfile.write(','.join(line.split(' ')))
            outfile.write('\n')
            
if __name__ == "__main__":
    P6('alkaline_metals.txt', 'output.txt')
