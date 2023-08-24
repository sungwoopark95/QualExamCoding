"""
“Dictionary of dictionaries”를 변수(argument)로 받아 
“inner dictionaries”가 모두 같은 key 값을 가지면 1, 아니면 0을 리턴하는 함수를 작성하시오.

<조건>
1. 딕셔너리가 비어있는 경우는 없음
2. 모든 value는 딕셔너리로 되어있음
3. value의 value는 딕셔너리 형태가 아님

TestCase1)
>>>P7({'a': {'aa':123, 'ab': [1,2]}, 'b': {'aa': 'bb', 'ab': 'cc'}})
1 (Explanation: 모든 value는 같은 key값, {'aa', 'ab'}를 갖는다.)
"""

def P7(dic):
    key_lst = []
    for sub_dic in dic.values():
        key_lst.append(sub_dic.keys())
        print('key list: ', key_lst)
    check = key_lst[0]
    for i in range(1, len(key_lst)):
        ans = 1
        if check != key_lst[i]:
            print(check, key_lst[i])
            ans = 0
    return ans    