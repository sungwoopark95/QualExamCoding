from typing import List

def hashtable(string:str) -> List[int]:
    # 'a'부터 'z'까지의 각 알파벳에 대한 빈도수를 0으로 초기화한 리스트 생성
    ans = [0 for _ in range(ord('a'), ord('z')+1)]
    
    # 문자열의 각 문자에 대해 해당 문자의 빈도수를 증가
    for c in string:
        idx = ord(c) - ord('a')  # 알파벳 'a'를 기준으로 한 문자의 인덱스 계산
        ans[idx] += 1
        
    return ans

def isAnagram(s: str, t: str) -> bool:
    # 주어진 문자열을 사용하여 알파벳 별 빈도수를 리스트로 반환하는 함수
    # 두 문자열 s와 t에 대한 빈도수 리스트 생성
    s_hash = hashtable(s)
    t_hash = hashtable(t)

    # 두 문자열의 빈도수 리스트가 동일한지 비교하여 결과 반환
    return s_hash == t_hash

if __name__ == "__main__":
    s = "anagram"
    t = "nagaram"
    # 두 문자열이 아나그램인지 확인하고 결과 출력
    print(isAnagram(s, t))
