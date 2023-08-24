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

# 단어를 사전순으로 정렬할 때 < or >로 비교해서 정렬 가능 & sorted(list)로도 가능
def P3(lst: list):
    # word 길이 저장한 dictionary 만듦
    dic = {}
    for word in lst:
        if word not in dic:
            dic[word] = len(word)
        else:
            continue
        
    ans = []
    i = 0
    lengths = set(dic.values()) # unique 길이만 저장함
    set_size = len(lengths) # set_size로 while loop돌면서 set element을 지워도 index 범위 안 벗어남
    # 가장 작은 길이의 단어 넣으면서 같은 길이면 sorted() 사용하여 사전순으로 넣기 
    while i < set_size:
        length = min(lengths) 
        same = [] # 새로운 가장 작은 길이 정해지면 같은 길이인 단어 넣은 array reset하기
        for k,v in dic.items():
            if v == length:
                same.append(k)   
        ans.extend(sorted(same))
        i += 1 
        lengths.remove(length)
    return ans