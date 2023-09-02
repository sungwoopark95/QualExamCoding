def beautySum(s: str) -> int:
    # substrings = []
    # for i in range(len(s)):
    #     for j in range(1, len(s)+1):
    #         substr = s[i:j]
    #         if len(substr) > 0:
    #             substrings.append(substr)
    
    # beauty = 0
    # for substr in substrings:
    #     freq = [0 for _ in range(ord('a'), ord('z')+1)]
    #     for char in substr:
    #         freq[ord(char)-ord('a')] += 1
    #     nonzeros = [item for item in freq if item > 0]
    #     beauty += max(nonzeros) - min(nonzeros)

    # return beauty
    ans = 0
    for i in range(len(s)):
        freq = dict()
        for j in range(i, len(s)):
            if s[j] in freq:
                freq[s[j]] += 1
            else:
                freq[s[j]] = 0
            beauty = max(freq.values()) - min(freq.values())
            # print(f"substring: {s[i:j]}, beauty: {beauty}")
            ans += beauty
    # print(ans)
    return ans