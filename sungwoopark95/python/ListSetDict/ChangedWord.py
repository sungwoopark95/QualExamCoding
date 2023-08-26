"""
# P10

“Query word” 주어지면 character중 하나를 꼭 바꿔서 “Changed word”를 만들어야 한다.

단어 집합(set)과 “Query word”를 변수(arguments)로 받아서 “Changed word”가 단어 집합 내의 단어와 하나라도 일치하면 True, 하나도 일치하지 않으면 False를 리턴하는 함수를 작성하시오.

<조건>
1. 모든 단어는 소문자 알파벳으로만 구성되고 띄어쓰기는 없음
2. “Query word”의 character 단 하나만 바꿀 수 있음
3. character를 바꿀 때 삭제는 할 수 없음

예시1) 
```
>>> P10({"data", "science"}, "data")
False
```

예시2) 
```
>>> P10({"data", "science"}, "daaa")
True (Explanation: "daaa"의 a 하나를 바꾸면 "data"를 만들 수 있다.)
```

예시3)
```
>>> P10({"data", "science"}, "scienzz")
False
```

예시4) 
```
>>> P10({"data", "science", "scienze"}, "scienzz")
True
```
"""

def P10(candidate:set, query:str):
    for word in candidate:
        if len(word) == len(query):
            cnt = 0
            for char1, char2 in zip(word, query):
                if char1 == char2:
                    cnt += 1
            if cnt == len(word) - 1:
                return True
    return False

if __name__ == "__main__":
    print(P10({"data", "science"}, "data"))
    print(P10({"data", "science"}, "daaa"))
