"""
[Find word]
문장 내에서 단어의 등장 위치를 찾는 함수 find word 를 작성하라. 
문장에서 단어는 공백, 쉼표(,), 및 마침표 (.)로 구분된다. 
또한, 단어가 일치함을 확인할 때 대소문자는 구분하지 않는다. 
주어진 단어가 문장 내에서 몇번째 단어로 등장하는지 그 위치들을 구해 정수의 리스트로 반환한다 

TestCase)
s = "Some feelings are shallow, some feelings are deep. Some make us smile, some make us weap."
print(find_word(s, "feelings"))
print(find_word(s, "FeelinGs"))
print(find_word(s, "some"))
print(find_word(s, "python"))

[1, 5]
[1, 5]
[0, 4, 8, 12]
[]
"""

def find_word(s: str, word: str):
    stc = s.split()
    ans = []
    # print(stc)
    for i in range(len(stc)):
        if stc[i].lower() == word.lower():
            ans.append(i)
    return ans