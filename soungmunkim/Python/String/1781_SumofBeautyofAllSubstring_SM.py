"""
Sum of Beauty of all substring

[최대 char 빈도수 - 최소 char 빈도수 = beauty of string]
The beauty of a string is the difference in frequencies between the most frequent and least
frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2 .
Given a string s , return the sum of beauty of all of its substrings.
"""

def charCounter(sub):
    counter = dict()
    for i in range(len(sub)):
        if sub[i] not in counter:
            counter[sub[i]] = 1
        else:
            counter[sub[i]] += 1
    return counter
    
    

def beautySum(s):
    # 모든 가능한 substring 뽑기
    sumbeauty = 0
    
    for i in range(len(s)):
        for j in range(i, len(s)):
            sub = s[i:j+1]
            sub_counter = charCounter(sub)
            
            min_cnt = 1000000
            max_cnt = 0
            
            for val in sub_counter.values():
        
                if val < min_cnt:
                    min_cnt = val
                if val > max_cnt:
                    max_cnt = val
            
            beauty_cnt = max_cnt - min_cnt
            sumbeauty += beauty_cnt
                
    return sumbeauty