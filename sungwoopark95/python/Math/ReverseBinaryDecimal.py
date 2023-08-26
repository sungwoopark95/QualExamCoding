"""
0 이상 정수 `num`을 입력으로 받는다. 
`num`을 32bit로 나타낸 다음 (반드시 32bit로 나타내어야 한다. 앞자리 수가 비더라도 `0`으로 채워서 32자리를 맞춰야 함), 
bit를 거꾸로 뒤집었을 때의 값을 0 이상의 10진수 정수로 return 하는 `P2` 함수를 구현하시오. 
"""
def P2(n:int):
    def bit32(num:int):
        container = []
        while num > 1:
            container.append(str(num % 2))
            num = num // 2
        container.append(str(num))
        container.reverse()
        ans = ''.join(container)
        if len(ans) < 32:
            to_add = '0' * (32 - len(ans))
            ans = to_add + ans
        return ans
    
    def bin2dec(binary:str):
        ans = 0
        for i, c in enumerate(binary):
            ans += (2**(len(binary)-i-1)) * int(c)
        return ans
    
    target = bit32(n)[::-1]
    return bin2dec(target)
