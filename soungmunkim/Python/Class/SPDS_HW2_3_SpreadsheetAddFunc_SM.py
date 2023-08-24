"""
[spread sheet에 함수 적용해보기]
다른 셀 한 개를 참조하는 lambda function을 특정 셀에 입력할 수 있도록 기능을 제공하는 class SmarSpreadsheet를 구현하라.
SmartSpreadsheet는 Spreadsheet를 상속한 class로 구현한다. 

추가로 구현해야할 method는 아래와 같다.
• set function(idx, function, operand idx)
    idx가 가리키는 스프레드시트의 셀 한 개에 함수 function을 입력한다. 
    function은 입력 값 한 개를 받는 python lambda function이다. 
    operand idx는 function의 인자로 들어갈 셀의 index이다 
    (예: ‘B3’). 함수 실행 이후 get value(idx)를 실행하거나 SmartSpreadsheet object 자체를 print할 경우, 
    operand idx 셀 값을 function에 인자로 넣어 얻은 계산 결과를 idx 셀 값으로 사용한다.

함수 구현 시 아래와 같은 사항을 유의하여야 한다.
• 셀 참조는 Microsoft Excel과 마찬가지로, 참조하는 셀의 값이 변하면 수식 계산 결과도 바뀌어야 한다.
    즉 operand idx 셀의 값을 바꾼 후 idx셀의 값을 확인하면 바뀐 값을 반영한 계산 결과를 반환해야한다.
• operand idx 셀도 다른 셀을 참조하는 셀일 수 있음을 유의하여야 한다.
• 입력한 lambda function은 int, bool, 혹은 string을 입력으로 받아 int, bool, 
    혹은 string을 반환 하는 함수라고 가정한다. 
    lambda function이 잘못된 타입의 인자/반환값을 사용하거나 Exception을 발생시키는 경우는 없다고 가정한다.
• 순환 참조는 일어나지 않는다고 가정한다. 예를 들어 A3이 A1의 값을 참조하고 A1이 A3을 참조하는 경우는 없다고 가정한다.
• 문제 2와 문제 3은 별개이다. SmartSpreadsheet에 대해 import sheet, export sheet method를 구현할 필요는 없다.
"""
from SPDS_HW2_1_Spreadsheet_SM import Spreadsheet

class SmartSpreadsheet(Spreadsheet):
    """
    SmartSpreadsheet는 Spreadsheet의 자식 클래스입니다. 
    SmartSpreadsheet는 한 셀에서 다른 셀에 람다 함수를 적용할 수 있는 메서드를 가지고 있습니다.
    Spreadsheet 클래스와 달리 set_function 함수가 추가되었습니다.
    """
    # 람다 함수의 종속성을 처리하는 데 필요한 정보를 저장하기 위한 글로벌 변수
    operand = []

    def set_function(self, idx, function, operand_idx):
        """
        idx 셀에 operand_idx 셀의 값을 function(람다 함수)에 적용한 결과를 설정합니다.
        또한, 이 함수, 피연산자 및 인덱스 정보를 operand에 저장합니다.
        """
        # idx 셀에 operand_idx 셀의 값을 function에 적용한 결과를 설정합니다.
        self.set_value(idx, function(self.get_value(operand_idx)))
        
        # function, operand 및 idx를 operand에 저장합니다.
        # 단, 동일한 정보가 이미 저장되어 있지 않은 경우에만 저장합니다.
        if [operand_idx, function, idx] not in SmartSpreadsheet.operand:
            SmartSpreadsheet.operand.append([operand_idx, function, idx])
        
    def set_value(self, idx, value):
        """
        idx 셀에 주어진 값을 설정하는 메서드입니다.
        또한, idx 셀의 값이 변경된 경우 이 셀에 종속된 다른 셀의 값을 업데이트합니다.
        """
        # 주어진 값을 idx 셀에 설정합니다.
        super().set_value(idx, value)
        
        # operand에 저장된 모든 종속성 정보를 확인하여 필요한 경우 값을 업데이트합니다.
        for i in range(len(SmartSpreadsheet.operand)):
            # 현재 종속성 정보의 피연산자 인덱스가 idx와 일치하는지 확인합니다.
            if SmartSpreadsheet.operand[i][0] == idx:
                # 일치하는 경우 해당 종속성 정보를 사용하여 값을 업데이트합니다.
                self.set_function(SmartSpreadsheet.operand[i][2], SmartSpreadsheet.operand[i][1], SmartSpreadsheet.operand[i][0])
