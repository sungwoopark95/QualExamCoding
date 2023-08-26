"""
아래의 예시와 같이 숫자의 일부 자릿수를 영어로 바꾸는 변환기가 있다고 하자. 

<숫자의 일부 자릿수를 영어로 바꾼 예시> 
* 1234 → “one23four” 
* 98765 → “9eight7six5” 
* 423 → “fourtwo3 

위와 같이 숫자의 일부 자릿수가 영어로 바뀌었거나 혹은 바뀌지 않고 숫자 그대로인 문자열(string) `s`를 parameter로 받고, 해당 string을 다시 숫자(int)로 변환하여 return하는 함수 `P2`를 완성하라. 

이때, string method를 사용하지 않고 구현해야 한다. 

(힌트: ASCII  코드를 통해 해당 문자가 숫자 문자(ex. ‘1’)인지 알파벳(ex. ‘a’)인지 구분할 수 있다.)  

참고로 각 숫자에 대응하는 영단어는 다음과 같다. 

| 숫자 |  영단어  |
|:---:|:------:|
|  0  |  zero  |
|  1  |  one   |
|  2  |  two   |
|  3  |  three |
|  4  |  four  |
|  5  |  five  |
|  6  |  six   |
|  7  |  seven |
|  8  |  eight |
|  9  |  nine  |
"""

def P2(s:str):
    convert = {
        "zero": '0', "one": '1', "two": '2', "three": '3', "four": '4', "five": '5', 
        "six": '6', "seven": '7', "eight": '8', "nine": '9', "ten": '10'
    }
    num_ascii = [i for i in range(ord('0'), ord('9')+1)]
    char_ascii = [i for i in range(ord('a'), ord('z')+1)]
    
    ans = ""
    key = ""
    for c in s:
        if ord(c) in num_ascii:
            ans += c
        elif ord(c) in char_ascii:
            key += c
            if key in convert.keys():
                ans += convert[key]
                key = ""
    return int(ans)
    
if __name__ == "__main__":
    print(P2("one23four"))
    print(P2("nineeight76five"))
