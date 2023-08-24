"""
[저장 가능한 spreadsheet (import, export)]
스프레드시트의 현재 상태를 파일에 저장하고, 
추후 불러올 수 있도록 기능을 제공하는 class PermanentSpread- sheet를 구현하라. PermanentSpreadsheet는 Spreadsheet를 상속한 class로 구현한다. 추가로 구현해야 할 method는 아래와 같다.
• export sheet(filename)
    현재 PermanentSpreadsheet object의 상태를 filename 파일에 저장한다. 
    포맷은 무관하다. 
    동일한 이름 의 파일이 이미 있을 경우, 해당 파일을 덮어쓴다. 
    filename은 string object이며, 다른 타입의 입력이 들어올 경우 TypeError를 생성한다.
• import sheet(filename)
    현재 PermanentSpreadsheet object에 저장된 내용을 모두 버리고, 
        이전에 export sheet method로 file-name 파일에 저장해 둔 PremanentSpeadsheet를 다시 불러온다.
    두 method 모두 파일 처리와 관련하여 문제에서 정의하지 않은 에러를 처리할 필요는 없다. 
    예를 들어 invalid한 filename을 사용하는 경우, 
        import sheet 함수 실행 시 filename 파일이 없는 경우 등은 테스트하지 않는다.
"""
from SPDS_HW2_1_Spreadsheet_SM import Spreadsheet

class PermanentSpreadsheet(Spreadsheet):
    def export_sheet(self, filename):
        # filename이 문자열이 아닌 경우 TypeError를 발생시킵니다.
        if not isinstance(filename, str):
            raise TypeError("filename must be a string")
        
        # 파일을 쓰기 모드로 열고 스프레드시트의 모든 셀 값을 저장합니다.
        with open(filename, 'w') as file:
            # 10x10 크기의 스프레드시트를 순회합니다.
            for i in range(10):
                for j in range(10):
                    cell_value = self.matrix[i][j]
                    # 셀 값이 None이 아니면 (즉, 어떤 값이 저장되어 있다면) 해당 셀의 값을 파일에 저장합니다.
                    if cell_value is not None:
                        # 셀의 인덱스 (예: A1, B2 등)와 값을 ':'로 구분하여 파일에 씁니다.
                        file.write(f"{chr(65 + j)}{i+1}:{cell_value}\n")

    def import_sheet(self, filename):
        # filename이 문자열이 아닌 경우 TypeError를 발생시킵니다.
        if not isinstance(filename, str):
            raise TypeError("filename must be a string")
        
        # 스프레드시트의 모든 셀을 None으로 초기화합니다.
        self.matrix = [[None for _ in range(10)] for _ in range(10)]
        
        # 파일을 읽기 모드로 열어 저장된 값을 불러옵니다.
        with open(filename, 'r') as file:
            for line in file:
                # 각 줄에서 셀의 인덱스와 값을 ':'로 구분하여 추출합니다.
                cell_index, cell_value = line.strip().split(":")
                # 추출한 셀의 인덱스와 값을 스프레드시트에 설정합니다.
                self.set_value(cell_index, cell_value)
