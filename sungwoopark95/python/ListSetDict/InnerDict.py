"""
# P7

때때로 프로그래머들은 value가 딕셔너리로 이루어진 “Dictionary of dictionaries”를 간단한 데이터베이스로 이용한다. 

key가 문자열(string)이고 value가 딕셔너리 형태인 “Dictionary of dictionaries”를 다음과 같이 나타낼 수 있고, 이때 value는 “inner dictionary”라 한다.

```py
{ 'jgoodall' : {'surname' : 'Goodall',
                'forename' : 'Jane',
                'born' : 1934,
                'died' : None,
                'notes' : 'primate researcher',
                'author' : ['In the Shadow of Man','The Chimpanzees of Gombe']},
    'rfranklin' : {'surname' : 'Franklin',
                'forename' : 'Rosalind',
                'born' : 1920,
                'died' : 1957,
                'notes' : 'contributed to discovery of DNA'},
    'rcarson' : {'surname' : 'Carson',
                'forename' : 'Rachel',
                'born' : 1907,
                'died' : 1964,
                'notes' : 'raised awareness of effects of DDT',
                'author' : ['Silent Spring'] }
```

“Dictionary of dictionaries”를 변수(argument)로 받아 “inner dictionaries”가 모두 같은 key 값을 가지면 1, 아니면 0을 리턴하는 함수를 작성하시오.

<조건>
1. 딕셔너리가 비어있는 경우는 없음
2. 모든 value는 딕셔너리로 되어있음
3. value의 value는 딕셔너리 형태가 아님

예시1)
```
>>> P7({'a': {'aa':123, 'ab': [1,2]}, 'b': {'aa': 'bb', 'ab': 'cc'}})
1 (Explanation: 모든 value는 같은 key값, {'aa', 'ab'}를 갖는다.)
```

예시2) 
```
>>> P7({'A': {1: 'a', 2: 'b'}, 'B': {2: 'c', 3: 'd'}})
0
```
"""

from typing import Dict

def P7(dct:Dict):
    prev_keys = None
    for i, key in enumerate(dct):
        subdict = dct[key]
        if i == 0:
            prev_keys = subdict.keys()
            continue
        if prev_keys != subdict.keys():
            return 0
    return 1

if __name__ == "__main__":
    print(P7({'a': {'aa':123, 'ab': [1,2]}, 'b': {'aa': 'bb', 'ab': 'cc'}}))
    print(P7({'A': {1: 'a', 2: 'b'}, 'B': {2: 'c', 3: 'd'}}))
