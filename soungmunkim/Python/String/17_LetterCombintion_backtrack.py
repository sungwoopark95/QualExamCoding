"""
[숫자패드에 letters가 써있는 핸드폰 생각하기]
[ 해당 숫자패드의 letters의 모든 조합 리턴하는 방식]

Given a string containing digits from 2-9 inclusive, 
return all possible letter combinations that the number could represent. 
Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. 
Note that 1 does not map to any letters.


Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]
"""

def letterCombinations(digits: str) -> List[str]:
    
    phone = {
        "2": "abc",
        "3": "def",
        "4": "ghi",
        "5": "jkl",
        "6": "mno",
        "7": "pqrs",
        "8": "tuv",
        "9": "wxyz"
    }
    ans = []
    
    if len(digits) == 0:
        return ans
    # 숫자 하나만 있으면
    elif len(digits) == 1:
        for ch in phone[digits]:
            ans.append(ch)  
        return ans  
    
    def backtrack(combination, next_digit):
        if len(next_digit) == 0: # digits이 더이상 없으면
            ans.append(combination)
            
        else:
            # 현재 digits의 첫번째에 해당되는 letters 돌기
            for letter in phone[next_digit[0]]:
                # 다음 digit으로 넘어가기
                backtrack(combination+letter, next_digit[1:])
    
    backtrack('', digits)
    return ans