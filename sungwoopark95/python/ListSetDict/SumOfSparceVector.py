"""
두 벡터의 합은 같은 위치에 있는 원소들을 원소끼리 더하는 것이다. (element-wise sum)
예를 들어 [1,2,3]과 [4,5,6]의 합은 [5,7,9]이다.
모든 원소가 정수이고, 딕셔너리 형태로 저장된 두 개의 sparse vector를 변수(arguments)로 받아 
그들의 합을 새로운 딕셔너리로 저장하여 리턴하는 함수를 작성하시오.

TestCase1)
>>> P8({0: 1, 6: 3}, {0: 2, 5: 2, 6: 2, 7: 1}) 
{0: 3, 5: 2, 6: 5, 7: 1}
"""
from typing import Dict

def P8(a:Dict, b:Dict):
    if len(a.keys()) < len(b.keys()):
        base_dict, oppo_dict = b, a
    else:
        base_dict, oppo_dict = a, b
    
    ans = base_dict
    for key in oppo_dict:
        if key in ans:
            ans[key] += oppo_dict[key]
        else:
            ans[key] = oppo_dict[key]
    return ans

if __name__ == "__main__":
    print(P8({0: 1, 6: 3}, {0: 2, 5: 2, 6: 2, 7: 1}))
