"""
“Query word” 주어지면 character중 하나를 꼭 바꿔서 “Changed word”를 만들어야 한다.
단어 집합(set)과 “Query word”를 변수(arguments)로 받아서 
“Changed word”가 단어 집합 내의 단어와 하나라도 일치하면 True, 
하나도 일치하지 않으면 False를 리턴하는 함수를 작성하시오.

<조건>
1. 모든 단어는 소문자 알파벳으로만 구성되고 띄어쓰기는 없음 
2. “Query word”의 character 단 하나만 바꿀 수 있음

TestCase1)
>>> P10({"data", "science"}, "data") 
False
TestCase2)
>>> P10({"data", "science"}, "daaa")
True (Explanation: "daaa"의 a 하나를 바꾸면 "data"를 만들 수 있다.)
"""

def P10(words, word):
    lst = []
    for wrd in words:
        if len(wrd) == len(word):
            lst.append(wrd)
    
    i = 0
    j = 0
    cnt = 0
    while j != len(lst):
        # word 뽑기
        w = lst[j]
        
        # chr 다르면 count +1 하기
#         print('i: ', i)
#         print('word: ', w, word)
        if w[i] != word[i]:
            cnt += 1
        i+=1
        
        # chr마다 다 돌면 다른 단어로 넘어가기 (cnt, i reset하기)
        # 만약 한 chr만 다르면 바로 true return하기
        if i == len(lst[j]):
            if cnt == 1:
                return True
            i=0
            j+=1
            cnt=0
    return False