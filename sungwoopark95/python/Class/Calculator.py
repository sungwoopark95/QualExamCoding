"""
윈도우에 있는 기본 계산기처럼 동작을 하는 `Calculator` 클래스를 구현해야 한다.
"""

class Calculator:
    def __init__(self):
        self.num = ""
        self.command = ["+"]
    
    def clear(self):
        self.num = ""
        self.command = ["+"]
        
    def digit(self, num):
        self.num += str(num)
    
    def plus(self):
        if len(self.num) > 0:
            self.command.append(int(self.num))
        else:
            self.command.append(0)
        
        if self.command[-1] in ["+", "-"]:
            self.command[-1] = "+"
        else:
            self.command.append("+")
        
        self.num = ""
        
    def minus(self):
        if len(self.num) > 0:
            self.command.append(int(self.num))
        else:
            self.command.append(0)
        
        if self.command[-1] in ["+", "-"]:
            self.command[-1] = "-"
        else:
            self.command.append("-")
        
        self.num = ""    
    
    def equal(self):
        if len(self.num) > 0:
            self.command.append(int(self.num))
        else:
            self.command.append(0)
        
        ans = 0
        for i in range(0, len(self.command), 2):
            sublist = self.command[i:i+2]
            sign, number = sublist
            if sign == "+":
                ans += number
            else:
                ans -= number
        return ans
    
if __name__ == "__main__":
    c = Calculator() 
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
    print(c.equal())
