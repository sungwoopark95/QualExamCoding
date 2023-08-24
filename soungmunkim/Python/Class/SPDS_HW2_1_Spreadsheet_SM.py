"""
[spreadsheet 만들기]

Microsoft Excel과 유사하게 데이터를 저장하고 읽을 수 있는 스프레드시트를 class Spreadsheet로 구현하라. 

Spreadsheet의 제약조건은 아래와 같다.
• 스프레드시트는 10개의 row, 10개의 column으로 구성된다. 
    Microsoft Excel과 유사하게 column은 알파벳(A, B, ..., J, 혹은 a, b, ..., j)으로, 
    row는 정수(1, 2, 3, ..., 10)로 indexing한다.
• 스프레드시트의 각 셀은 int, bool, string을 저장할 수 있다. 
    이 때 string은 whitespace 문자(\n, \t, space 등)를 포함하지 않는다고 가정한다.
• 생성자는 별도의 입력을 받지 않는다.
• Spreadsheet object를 print할 경우, Spreadsheet에 저장된 내용이 출력되어야 한다. 
    이 때 한 row 내의 element 사이는 comma(,) 한 개로 구분하고, row 사이는 개행(\n) 한 개로 구분하도록 하여 출력한다. 출력을 보기 좋게 만들기 위해 임의로 whitespace를 추가하여도 된다

      ,       , True  ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
5     ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       , hello ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
      ,       ,       ,       ,       ,       ,       ,       ,       ,       , 
"""


class Spreadsheet:
    def __init__(self):
        self.index = {'A':0, 'B':1, 'C':2, 'D':3, 'E':4, 'F':5, 'G':6, 'H':7, 'I':8, 'J':9}
        self.matrix = [[None for _ in range(10)] for _ in range(10)]
        
        """
        self.matrix_ = []
        for _ in range(10):
            self.row = []
            for _ in range(10):
                self.row.append(None)
            self.matrix_.append(self.row)
        """
        
    def __str__(self):
        # 각 셀의 최대 너비를 찾습니다.
        max_width = 0
        for row in self.matrix:
            for cell in row:
                # 현재 셀의 너비를 계산합니다.
                if cell is not None:
                    cell_width = len(str(cell))
                    # 현재 셀의 너비가 지금까지 찾은 최대 너비보다 크다면 업데이트합니다.
                    if cell_width > max_width:
                        max_width = cell_width

        # 테이블 초기화
        table = ""
        
        for i in range(len(self.matrix)):
            for j in range(len(self.matrix[i])):
                if self.matrix[i][j] == None:  # None일 때 빈칸 + , 로 print
                    table += ' ' * max_width + " , "
                else:  # value가 있다면 string 처리해서 , 붙이기 (가운데 정렬하기 center()) 
                    # 오른쪽으로 정렬하고 싶으면 rjust()
                    table += str(self.matrix[i][j]).ljust(max_width) + " , "
            table += "\n"  # row 끝나면 다음 col로 넘어가기
        return table
    
    def set_value(self, idx: str, value):
        if isinstance(idx, str):
            # A1 처럼 2 char이 들어온 게 아니라면 error
            if len(idx) != 2:
                raise IndexError("Invalid Index")
        
        
            # column: 알파벳, row: 정수
            j, i = idx
            i = int(i)
            
            # 들어온 알파벳이 index dictionary에 없다면 error
            if j not in self.index:
                raise IndexError("Invalid Index")
            else:
                # 해당 알파벳 key의 value 가져오기
                j_idx = self.index.get(j)
            # 들어온 정수가 0-9가 아니라면 error (들어오는 정수가 1-10이니까)
            if i-1 < 0 and i-1 > 9:
                raise IndexError("Invalid Index")
            
            # int, bool, string일 때 해당 index에 value 넣기
            if (isinstance(value, str) or isinstance(value, int) or isinstance(value, bool)):
                self.matrix[i-1][j_idx] = value
            else:
                raise TypeError("Value must be string, boolen, or interger.")
        else:
            # index가 string이 아니라면 error
            raise TypeError('Index only accepts string.')
        
    def get_value(self, idx:str):
            if isinstance(idx, str):
                # A1 처럼 2 char이 들어온 게 아니라면 error
                if len(idx) != 2:
                    raise IndexError("Invalid Index")
            
                # column: 알파벳, row: 정수
                j, i = idx
                i = int(i)
                
                # 들어온 알파벳이 index dictionary에 없다면 error
                if j not in self.index:
                    raise IndexError("Invalid Index")
                else:
                    j_idx = self.index.get(j)
                # 들어온 정수가 0-9가 아니라면 error (들어오는 정수가 1-10이니까)
                if i-1 < 0 and i-1 > 9:
                    raise IndexError("Invalid Index")
            else:
                # index가 string이 아니라면 error
                raise TypeError('Index only accepts string.')
            
            return self.matrix[i-1][j_idx]