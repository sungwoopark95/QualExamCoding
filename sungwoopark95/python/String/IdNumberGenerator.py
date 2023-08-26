"""
대한민국의 주민등록번호 13자리 중 앞 7자리는 다음 규칙에 의해 생성된다. 
앞의 6자리는 생년월일을 가리키고, 7번째 자리는 태어난 년도와 성별에 따라 나뉜다. 
1900년대 태생 남성은 1, 여성은 2, 2000년대 남성은 3, 여성은 4, 1800년대 남성은 9,  여성은 0을 부여한다. 
예를 들어 1956년 2월 14일 생 남성은 ‘5602141’로 표현된다. 
이와 같이 성별, 생년월일이 리스트로 주어졌을 때 주민등록번호 앞 7자리를 알맞게 형성하여 return하는 함수 `P3`를 완성하라. 

<조건> 
1. input parameter는 항상 `[str sex, int birth_year, int birth_month, int birth_day]` 꼴이라고 가정 
2. 성별은 `‘MALE’` 혹은 `‘FEMALE’` 중 하나로 표현됨 
3. input으로 타당하지 않은 날짜가 들어가지 않음 (ex. 2000-02-30 or 1999-13-12) 
4. return 타입은 string(문자열) 
"""

def P3(info:list):
    def tostr(num:int):
        if num >= 10:
            return str(num)
        return '0'+str(num)
    
    last_digit = {
        (18, 'MALE'): 9, (18, "FEMALE"): 0, (19, 'MALE'): 1, 
        (19, 'FEMALE'): 2, (20, 'MALE'): 3, (20, 'FEMALE'): 4
    }
    
    gender, year, month, day = info
    year_front, year_rear = year // 100, year % 100
    
    return tostr(year_rear) + tostr(month) + tostr(day) + str(last_digit[(year_front, gender)])

if __name__ == "__main__":
    print(P3(['MALE', 1956, 2, 14]))
    print(P3(['MALE', 1996, 10, 30]))
