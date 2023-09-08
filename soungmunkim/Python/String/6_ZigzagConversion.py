"""
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: 
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
 
Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"
"""

"""
convert 함수의 작동 원리를 "PAYPALISHIRING" 문자열과 numRows = 3를 사용하여 설명하겠습니다.

입력: s = "PAYPALISHIRING", numRows = 3
초기 상태: rows = ["", "", ""], index = 0, step = 1

첫 번째 문자 'P':
index가 0이므로 첫 번째 행에 'P'를 추가합니다.
rows = ["P", "", ""]
index가 0이므로 step은 1이 됩니다. (아래로 이동)

두 번째 문자 'A':
index를 증가시키고 (이제 index는 1입니다), 두 번째 행에 'A'를 추가합니다.
rows = ["P", "A", ""]

세 번째 문자 'Y':
index를 다시 증가시키고 (index는 이제 2입니다), 세 번째 행에 'Y'를 추가합니다.
rows = ["P", "A", "Y"]
index가 마지막 행이므로 step은 -1이 됩니다. (위로 이동)

네 번째 문자 'P':
index를 감소시키고 (이제 index는 1입니다), 두 번째 행에 'P'를 추가합니다.
rows = ["P", "AP", "Y"]

이런 패턴을 계속해서 문자열 끝까지 반복하면 최종적으로 rows는 아래와 같이 됩니다:
rows = ["PAHN", "APLSIIG", "YIR"]

마지막으로, rows의 모든 문자열을 연결하면 최종 결과인 "PAHNAPLSIIGYIR"을 얻을 수 있습니다.

이러한 방식으로 zigzag 패턴에 따라 문자를 행에 분배하고, 마지막에는 각 행의 문자들을 순차적으로 연결하여 결과 문자열을 생성합니다.
"""


def convert(s: str, numRows: int) -> str:
    # numRows가 1인 경우나, 문자열의 길이가 numRows보다 짧거나 같은 경우,
    # 별도의 zigzag 패턴 변환이 필요 없으므로 입력 문자열을 그대로 반환합니다.
    if numRows == 1 or len(s) <= numRows:
        return s
    
    # numRows만큼의 빈 문자열을 갖는 리스트를 생성합니다.
    # 각 문자열은 각 행에 해당하는 문자들을 저장할 것입니다.
    rows = [''] * numRows
    index, step = 0, 1  # index는 현재 행, step은 진행 방향(1 또는 -1)을 나타냅니다.
    
    # 입력된 문자열 s에 대해 한 문자씩 순회합니다.
    for char in s:
        # 현재 문자를 해당 행에 추가합니다.
        rows[index] += char
        
        # 만약 첫 행에 도달하면 아래로 이동해야 하므로 step을 1로 설정합니다.
        # 마지막 행에 도달하면 위로 이동해야 하므로 step을 -1로 설정합니다.
        if index == 0:
            step = 1
        elif index == numRows - 1:
            step = -1
        
        # 행 인덱스를 업데이트합니다.
        index += step

    # 모든 행의 문자들을 연결하여 최종 결과 문자열을 생성합니다.
    return ''.join(rows)
