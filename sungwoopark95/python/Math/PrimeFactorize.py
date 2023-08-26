"""
자연수를 parameter로 받고, 해당 자연수가 2개의 소수의 곱으로 표현된다면 `True`, 아니라면 `False`를 반환하는 함수 `P1`를 작성하라. 
"""

def P1(num:int):
    def check_prime(num:int):
        from math import sqrt
        if num == 1:
            return False
        for i in range(2, int(sqrt(num))+1):
            if num % i == 0:
                return False
        return True
    
    def get_primes(num:int):
        return [i for i in range(1, num+1) if check_prime(i)]
    
    primes = get_primes(num)
    for prime in primes:
        if num / prime in primes:
            return True
    return False

if __name__ == "__main__":
    print(P1(6))
    print(P1(9))
