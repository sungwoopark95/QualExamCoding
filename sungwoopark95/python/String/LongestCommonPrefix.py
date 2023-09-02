from typing import List

def longestCommonPrefix(strs: List[str]) -> str:
    # 우선 길이가 0인 string이 있으면 empty string 반환
    for word in strs:
        if len(word) == 0:
            return ""
    
    # 어차피 가장 길어봤자 가장 짧은 단어의 길이를 넘지 못함
    max_length = min([len(word) for word in strs])
    common = ""
    is_break = False
    for i in range(max_length):
        start = strs[0][i] # 첫 번째 단어의 i번째 글자
        for j in range(1, len(strs)):
            if strs[j][i] != start: # j번째 단어의 i번째 글자와 같은지 확인
                is_break = True # break로 종료되었다는 표시
                break
        # 반복을 모두 돌아 break로 종료되지 않은 경우, i번째 글자는 모든 단어에 걸쳐서 공통이라는 뜻
        if not is_break:
            common += start
    
    return common
