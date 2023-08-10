"""
성별, 생년월일이 리스트로 주어졌을 때 주민등록번호 앞 7자리를 알맞게 형성하여 return하는 함수

1. 6자리는 생년월일
2. 7번째 자리는 태어난 년도와 성별에 따라 나뉨
    1800년대 남: 9, 여: 0
    1900년대 남: 1, 여: 2
    2000년대 남: 3, 여: 4

<조건>
1. input parameter는 항상 [str sex, int birth_year, int birth_month, int birth_day] 꼴이라고 가정
2. 성별은 ‘MALE’ 혹은 ‘FEMALE’ 중 하나로 표현됨
3. input으로 타당하지 않은 날짜가 들어가지 않음 (ex. 2000-02-30 or 1999-13-12)
4. return 타입은 string(문자열)

TestCase1)
>>> P3(['MALE', 1956, 2, 14]) 
‘5602141’
"""
def P3(lst: list) -> str:
    
    
    if lst[0] == 'MALE':
        dic = {'18':'9', '19':'1', '20':'3'}
    else: 
        dic = {'18':'0', '19':'2', '20':'4'}
    
    key = str(lst[1])[:2]
    yr = str(lst[1])[2:]
    
    for_sex = dic.get(key)
    
    m = str(lst[2])
    d = str(lst[3])
    if len(m)<2:
        m = '0'+m
    if len(d)<2:
        d = '0'+d
    
    return yr+m+d+for_sex