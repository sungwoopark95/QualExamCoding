# I have copied the class code
def linear_search(l,e):
    n = len(l)
    idx = -1
    for i in range(n):
        if (l[i] == e):
            idx = i
    return idx

def binary_search(l,e):
    def bs(l,low,high,e):
        if low > high:
            return -1
        i = int((low+high)/2)
        if (l[i] == e):
            return i
        elif l[i] < e:
            i = bs(l,i+1,high,e)
        else:
            i = bs(l, low, i-1,e)
        return i
    
    # if l is not sorted sort l
    if (sorted(l) != l):
        l.sort()
    return bs(l, 0, len(l) - 1, e)