"""
두 문자열(string) `Order`와 `S`가 있다. `Order`의 모든 문자는 중복이 없고 어떤 규칙에 의해 이미 정렬되어 있다. `S`를 다음 규칙에 따라 수정하여 `Correct_S`라는 새로운 문자열을 만들려고 한다.

**규칙1>** 만약 `S`에 `Order`에 포함된 문자가 있으면 `Order`에서 사용된 규칙에 의해 우선 정렬되어야 한다.
**규칙2>** `Order`에 없는 문자에 대해서는 원래 `S`의 순서를 따르며, 규칙 1에서 정렬된 문자열 뒤에 나타내야 한다.
**규칙3>** `S`는 `Order`의 일부만 포함하거나 아예 포함하지 않는 경우, 중복된 경우도 있다.
"""

## sorted 함수를 사용하지 않고 문자열 S를 Order에 따라 정렬하는 함수
def P2(Order:str, S:str):
    # S 문자열을 리스트로 변환
    s_list = list(S)
    # s_list의 복사본 생성
    to_sort = s_list[:]
    # Order와 S의 문자 위치를 저장할 리스트 초기화
    in_order_idx = [-1 for _ in range(len(S))]
    in_s_idx = [-1 for _ in range(len(S))]
    
    # Order의 각 문자에 대해 S 내의 위치를 찾아 저장
    for idx, c_order in enumerate(Order):
        for jdx, c_s in enumerate(S):
            if c_order == c_s:
                in_order_idx[jdx] = idx
                in_s_idx[jdx] = jdx
    
    # in_order_idx를 기준으로 S와 in_s_idx를 정렬 (버블 정렬 사용)
    for i in range(len(in_order_idx)):
        for j in range(len(in_order_idx)-i-1):
            if in_order_idx[j] > in_order_idx[j+1]:
                in_order_idx[j], in_order_idx[j+1] = in_order_idx[j+1], in_order_idx[j]
                in_s_idx[j], in_s_idx[j+1] = in_s_idx[j+1], in_s_idx[j]
    
    # 정렬된 문자열을 저장할 리스트 초기화
    correct_S = []
    # Order에 따라 정렬된 문자를 correct_S에 추가
    for order_idx, s_idx in zip(in_order_idx, in_s_idx):
        if order_idx != -1:
            char = s_list[s_idx]
            to_sort.pop(s_idx)
            correct_S.append(char)
    
    # Order에 없는 문자들을 correct_S에 추가
    correct_S.extend(to_sort)
    
    # 리스트를 문자열로 변환하여 반환
    return ''.join(correct_S)

## sorted 함수 사용하는 경우
def P2_(Order, S):
    # Order에 있는 문자를 기준으로 정렬하되, Order에 없는 문자는 원래 순서를 유지하도록 정렬 함수를 정의합니다.
    def custom_sort(char):
        return (Order.index(char) if char in Order else len(Order), S.index(char))

    # S의 문자들을 custom_sort 함수를 기준으로 정렬합니다.
    Correct_S = ''.join(sorted(S, key=custom_sort))
    """
    1. 먼저 Order.index를 기준으로 정렬한다. 이때, Order에 있지 않은 문자들은 len(Order)로 주어, 항상 Order에 있는 문자들보다 뒤에 오게 한다.
    2. 이제 Order에 없는 문자들은 len(Order)로 index값이 모두 같으므로, 이제 S의 index로 
    """
    return Correct_S

if __name__ == "__main__":
    print(P2('cbafg', 'xabcd'))
    print(P2_('cbafg', 'xabcd'))
