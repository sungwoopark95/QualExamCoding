# I have copied the class code
def bubble_sort(l):
    def swap(i,j):
        # first save the first element
        t = l[i]
        # save the second element to first 
        l[i] = l[j]
        # save the first element to where the second element was
        l[j] = t
        return
    n = len(l) - 1
    for i in range(n,0,-1):
        for j in range(i):
            if (l[j] >= l[j+1]):
                swap(j,j+1)
    return l

def insertion_sort(l):
    n = len(l)
    for j in range(1,n):
        key = l[j]
        i = j-1
        while ((i>=0) and (key < l[i])):
            l[i+1] = l[i]
            i-=1
        l[i+1] = key
    return l

def selection_sort(l):
    def swap(i,j):
        t=l[i]
        l[i] = l[j]
        l[j] = t
        return
    n = len(l)
    for i in range(0, n-1):
        s = i
        swap_flag = False
        for j in range(i+1, n):
            if (l[s] >= l[j]):
                s = j
                swap_flag = True
        swap(i,s) if swap_flag else None  
    return l

def merge_sort(left, right):
    len_left, len_right = len(left), len(right)
    i_left, i_right = 0,0
    l=[]
    while ((i_left < len_left) and (i_right < len_right)):
        if (left[i_left] < right[i_right]):
            l.append(left[i_left])
            i_left +=1
        else:
            l.append(right[i_right])
            i_right +=1
    while (i_left < len_left):
        l.append(left[i_left])
        i_left +=1
    while (i_right < len_right):
        l.append(right[i_right])
        i_right +=1
    return l

def partition(l, low, high):
    p = l[low]
    small = []
    large = []
    
    for i in l[low + 1:high + 1]:
        if i < p:
            small.append(i)
        else:
            large.append(i)
    small.append(p) 
    
    idx = low
    for i in small:
        l[idx] = i
        idx += 1
    for i in large:
        l[idx] = i
        idx += 1
    
    return (low + len(small) - 1)

def quick_sort(l):
    #Original class code
    #def qs(l, low, high, n):
    #    if (low < high):
    #        pivot_idx = partition(l, low, high)
    #        qs(l, low, pivot_idx - 1, n+1)
    #        qs(l, pivot_idx + 1, high, n + 1)
    #    return l
    #qs(l, 0 , len(l) - 1, 0)
    #return l
    
    # Due to recursive error, I have tried to increase the maximum recursion but if recursion exceeds 22000,
    # kernel dies and because worst case for quick_sort require 100000 + 1, it was not possible.
    # I have tried suggestion to 10^6, but both computer and Google Colab was not able to handle
    # Second way to handle recursion was to change it to iterative version.
    
    # I will implement the version from this website and convert deque to version that does not use deque:
    # https://www.techiedelight.com/iterative-implementation-of-quicksort/
    
    if (len(l) == 1):
        return l
    
    else: 
        # get the starting and ending index of a given list => start = 0, end = len(a) - 1
        start = 0
        end = len(l) - 1
        
        # create a stack for storing sublist start and end index => stack = deque()
        stack = [0] * len(l)
        
        # push the start and end index of the array into the stack =>  stack.append((start, end))
        head = 0
        stack[head] = start
        head = head + 1
        stack[head] = end

        # loop till stack is empty => while stack:
        while head >= 0:
            # remove top pair from the list and get sublist starting and ending indices => start, end = stack.pop()
            end = stack[head]
            head = head - 1
            
            start = stack[head]
            head = head - 1

            # rearrange elements across pivot => pivot = partition(a, start, end) 
            p = partition(l, start, end)
            
            # push sublist indices containing elements that are less than the current pivot to stack
                # => if pivot - 1 > start: stack.append((start, pivot - 1))
            if p - 1 > start:
                head = head + 1
                stack[head] = start
                head = head + 1
                stack[head] = p - 1
            
            # push sublist indices containing elements that aremore than the current pivot to stack
                # => if pivot + 1 < end: stack.append((pivot + 1, end))
            if p + 1 < end:
                head = head + 1
                stack[head] = p + 1
                head = head + 1
                stack[head] = end
    return l


def counting_sort(l,m):
    c = [0] * (m + 1)
    for i in l:
        c[i] += 1
    
    for j in range(1, m + 1):
        c[j] = c[j-1] + c[j]
    
    n = len(l)
    t = [0] * n
    for i in range(n-1,-1,-1):
        j = l[i]
        t[c[j] - 1] = j
        c[j] = c[j] - 1
    for i in range(0,n):
        l[i] = t[i]
    return l

def radix_sort(l,d):
    for r in range(0,d):
        c = [0] * 10
        m = d - r - 1
        for i in l:
            # obtain length
            length = len(str(i))
            # if same, then not worry
            if length == d:
                key = int(str(i)[m])
            else:
                k = length - r - 1
                # if k is negative means out of bounds so 0
                if k < 0:
                    key = 0
                else:
                    key = int(str(i)[k])
            c[key] += 1
        for j in range(1,10):
            c[j] = c[j-1] + c[j]
        n = len(l)
        t = [0] * n
        for i in range(n-1,-1,-1):
            length = len(str(l[i]))
            if length == d:
                key = int(str(l[i])[m])
            else:
                k = length - r - 1
                # if k is negative means out of bounds so 0
                if k < 0:
                    key = 0
                else:
                    key = int(str(l[i])[k])
            t[c[key] - 1] = l[i]
            c[key] = c[key] - 1
        for i in range(0,n):
            l[i] = t[i]
    return l