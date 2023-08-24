"""
중첩 리스트(nested list)를 입력으로 받고, 아래 조건을 만족하는 리스트를 리턴하는 함수 P4를 작성

<조건>
1. 입력 리스트는 [[영단어, 글자수]] 꼴이며, 자세한 건 아래의 예시를 참고 
2. 영단어는 알파벳 소문자로만 이루어져 있음
3. 입력 리스트에서 단어만 모아서 리스트로 리턴
4. 리스트는 알파벳 순으로 정렬되어 있어야함

TestCase1)
>>> P4([['cup', 3], ['ace', 3], ['nice', 4], ['good', 4]]) 
['ace', 'cup', 'good', 'nice']
"""

def P4(nested_lst):
    ans = []
    for lst in nested_lst:
        # 만약 대문자가 섞여있다면, lst[0].lower()로
        ans.append(lst[0])
    ans.sort()
    
    return ans