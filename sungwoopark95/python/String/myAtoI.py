def myAtoi(s: str) -> int:
    # 숫자를 문자로 변환하여 리스트에 저장 (0~9까지)
    dictionary = [str(i) for i in range(10)]
    
    # 32-bit signed 정수의 최솟값과 최댓값 설정
    int_min, int_max = -(2**31), (2**31) - 1

    # 숫자가 처음 시작되는 위치를 찾는다.
    start = -1
    for i, c in enumerate(s):
        if c in dictionary:
            start = i
            break
    
    # 유효한 문자들을 찾아 문자열을 구성한다.
    string = ""
    sign_flag = False  # 부호(+, -)가 이미 발견되었는지 확인하는 플래그
    for j, c in enumerate(s):
        # 현재 문자가 부호인 경우
        if c in ["+", "-"]:
            # 숫자가 시작되기 전이고, 부호 플래그가 False일 때
            if j < start and not sign_flag:
                string += c
                sign_flag = True  # 부호를 발견했으므로 플래그를 True로 설정
            else:
                break
        # 현재 문자가 공백인 경우
        elif c == ' ':
            if j < start:
                if j == 0:
                    continue
                # 이전 문자가 공백일 경우
                if j > 0 and s[j-1] == ' ':
                    continue
                else:
                    break
            else:
                break
        # 현재 문자가 '.'인 경우 종료
        elif c == ".":
            break
        # 현재 문자가 숫자가 아닌 경우 종료
        elif c not in dictionary:
            break
        # 현재 문자가 숫자인 경우
        elif c in dictionary:
            string += c

    # 결과 문자열(string)이 비어있거나, "+" 또는 "-"만 포함하는 경우 0 반환
    if len(string) == 0 or string in ["+", "-"]:
        return 0
    # 결과 값이 최솟값보다 작으면 최솟값 반환
    if (int(string) < int_min):
        return int_min
    # 결과 값이 최댓값보다 크면 최댓값 반환
    if (int(string) > int_max):
        return int_max
    # 유효한 정수 값 반환
    return int(string)

if __name__ == "__main__":
    # 테스트 케이스 설정
    test_cases = ["42", "  +  413", "words and 987", "+-419332", 
                  "-4193-3219-22", "   -42", "42.195", "42 195"]
    
    # 각 테스트 케이스에 대해 myAtoi 함수 호출 및 결과 출력
    for case in test_cases:
        print(f"{case} -> {myAtoi(case)}")
