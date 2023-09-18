def isValid(s: str) -> bool:
    if len(s) % 2 == 1:
        return False
    valid = {"(": ")", "{": "}", "[": "]"}
    stack = []
    for c in s:
        if c in valid.keys():
            stack.append(c)
        else:
            if not stack or valid[stack[-1]] != c:
                return False
            stack.pop(-1)

    return not stack

if __name__ == "__main__":
    s_list = ["((()))","(()())","(())()","()(())","()()()"]
    for s in s_list:
        print(isValid(s))