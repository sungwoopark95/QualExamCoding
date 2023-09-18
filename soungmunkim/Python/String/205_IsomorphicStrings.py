"""
[Isomorphic string]
s가 서로 반대되는 char로 바꼈을때 t로 된다면 iosmorphic string임
ex) egg = add

Example 1:
Input: s = "egg", t = "add"
Output: true

Example 2:
Input: s = "foo", t = "bar"
Output: false

Example 3:
Input: s = "paper", t = "title"
Output: true
"""

def isIsomorphic(s: str, t: str) -> bool:
    mapping1 = dict()  # s의 문자를 t의 문자로 매핑하는 딕셔너리 초기화
    mapping2 = dict()  # t의 문자를 s의 문자로 매핑하는 딕셔너리 초기화

    # s와 t의 각 문자를 순회하며, 두 문자열 간의 문자 매핑을 딕셔너리에 저장
    for c_s, c_t in zip(s, t):
        mapping1[c_s] = c_t
        mapping2[c_t] = c_s
    # Example1 - add & egg -> True case
    # mapping1 = {'a': 'e', 'd': 'g'}
    # mapping2 = {'e': 'a', 'g': 'd'}
    
    # Example2 - foo & bar -> False case
    # mapping1 = {'f': 'b', 'o': 'r'} - dictionary는 key의 중복 허용 x
    # mapping2 = {'b': 'f', 'a': 'o', 'r': 'o'}
    
    compare1 = ""  # s를 t로 변환한 결과를 저장할 문자열 초기화
    compare2 = ""  # t를 s로 변환한 결과를 저장할 문자열 초기화

    # s와 t의 각 문자를 순회하며, 두 딕셔너리에 따라 문자열을 변환
    for c_s, c_t in zip(s, t):
        compare1 += mapping1[c_s]  # s의 문자에 따른 t의 문자로 변환
        compare2 += mapping2[c_t]  # t의 문자에 따른 s의 문자로 변환

    # 두 변환된 문자열이 각각 원래의 t와 s와 동일한지 확인
    # 동일하다면 두 문자열은 isomorphic
    if compare1 == t and compare2 == s:
        return True
    return False  # 두 문자열이 isomorphic하지 않다면 False 반환