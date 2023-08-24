"""
다음 조건을 만족하는 리스트(list)가 있다.
1. 모든 원소는 알파벳 소문자로 된 문자열(string)이다. (공백 없음) 
2. 각 string의 길이는 1 이상 20 이하이다.

<조건>
1. 길이가 짧은 문자열이 앞에 있어야 한다.
2. 길이가 같다면 사전 순서가 빠른 문자열이 앞에 있어야 한다.

TestCase1)
>>>P3(['solve', 'this', 'problem', 'or', 'you', 'will', 'get', 'f']) 
['f', 'or', 'get', 'you', 'this', 'will', 'solve', 'problem']
TestCase2)
>>>P3(['computing', 'class', 'is', 'so', 'funny', 'haha']) ['is', 'so', 'haha', 'class', 'funny', 'computing']
"""

def P3_ans(lst: list):
    ### Write code here ###
    lst.sort()
    lst.sort(key=len)
    
    return lst
    ### End of your code ###