"""
아래의 예시와 같이 숫자의 일부 자릿수를 영어로 바꾸는 변환기가 있다고 하자. 
<숫자의 일부 자릿수를 영어로 바꾼 예시>
→ “one23four” 
→ “9eight7six5”
→ “fourtwo3
문자열(string) s를 parameter로 받고, 해당 string을 다시 숫자(int)로 변환하여 return하는 함수 P2를 완성하라.

<조건>
1. 입력문자열 s의 길이는 1이상 50이하이다.
2. 입력 문자열 s 가 “zero” 혹은 “0”으로 시작하는 경우는 없다. 3. 유효하지 않은 입력은 없다고 가정
4. string method를 사용하지 말 것! (ex. replace, find, index 등)

TestCase1)
>>> P2("one23four") 
1234
"""
def P2(word: str):
    dic = {'zero':'0', 'one':'1', 'two':'2', 'thre':'3','four':'4', 'five':'5', 'six':'6', 'seven':'7','eight':'8', 'nine':'9'}
    not_num = ""
    num = ""
    for char in word:
        if ord(char) >= 97:
            not_num+=char
            # 해당 숫자 있으면 바꿔주고 reset
            if not_num in dic:
                num+=dic.get(not_num)
                not_num = ""
        # 숫자면 그냥 넣기
        else: num+=char
     
    ans = int(num)
    
    return ans