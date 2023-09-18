# 윈도우에 있는 기본 계산기처럼 동작을 하는 `Calculator` 클래스를 구현한다.
class Calculator:
    def __init__(self):
        # 초기화 함수. 계산기가 처음 시작할 때 실행된다.
        self.num = ""  # 현재 입력 받은 숫자를 저장하는 문자열
        self.command = ["+"]  # 연산과 숫자를 저장하는 목록. 기본 연산은 '+'

    def clear(self):
        # 모든 입력과 연산을 초기화하는 함수
        self.num = ""
        self.command = ["+"]

    def digit(self, num):
        # 숫자 입력을 처리하는 함수
        self.num += str(num)  # 입력받은 숫자를 현재 문자열에 추가

    def plus(self):
        # 더하기 연산을 처리하는 함수
        if len(self.num) > 0:
            # num에 저장된 숫자가 있다면 command에 추가
            self.command.append(int(self.num))
        else:
            # 없다면 0을 추가
            self.command.append(0)

        if self.command[-1] in ["+", "-"]:
            # 마지막으로 저장된 연산이 '+' 혹은 '-'라면 '+'로 변경
            self.command[-1] = "+"
        else:
            # 아니라면 '+' 연산을 추가
            self.command.append("+")

        self.num = ""  # 현재 입력된 숫자를 초기화

    def minus(self):
        # 빼기 연산을 처리하는 함수
        if len(self.num) > 0:
            self.command.append(int(self.num))
        else:
            self.command.append(0)

        if self.command[-1] in ["+", "-"]:
            self.command[-1] = "-"
        else:
            self.command.append("-")

        self.num = ""  # 현재 입력된 숫자를 초기화
    
    def equal(self):
        # 현재까지의 연산 결과를 반환하는 함수
        if len(self.num) > 0:
            self.command.append(int(self.num))
        else:
            self.command.append(0)
        
        ans = 0  # 결과값을 저장할 변수 초기화
        # command 목록을 돌면서 연산을 수행
        for i in range(0, len(self.command), 2):
            sublist = self.command[i:i+2]  # 연산자와 숫자를 함께 가져옴
            sign, number = sublist  # 연산자와 숫자 분리
            if sign == "+":
                ans += number
            else:
                ans -= number
        self.clear()
        return ans  # 결과 반환

# 메인 실행 영역
if __name__ == "__main__":
    c = Calculator()  # 계산기 객체 생성
    # 숫자와 연산 입력
    c.digit(1) 
    c.digit(2) 
    c.plus() 
    c.minus() 
    c.digit(3) 
    c.digit(1) 
    c.digit(2) 
    c.plus() 
    c.minus() 
    c.minus() 
    c.plus() 
    c.digit(0) 
    c.digit(0) 
    c.digit(1) 
    c.digit(0) 
    c.digit(0) 
    print(c.equal())  # 결과 출력
