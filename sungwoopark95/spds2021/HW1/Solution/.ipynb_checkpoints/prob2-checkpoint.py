def list_accumulator(n):
    """ 
    list_accumulator 함수 구현
    
    The program takes list as input and output cumulative sum of a given list.
    
    For this problem, because we do not know how many nested list will be present, it is wise to break down the problem as recursive.
    The base case will be adding value to total amount where for the recursive case, it will check if value is list and repeat the process.
    After iteration, the function will return cumulative sum of a given list.
    """
    
    # Initialize the total amount
    total = 0
    
    # Iterate through the list
    for i in n:
        # If the element is list, then go to recursive case by adding it to the total amount.
        if isinstance(i,list):
            total = total + list_accumulator(i)
        else:
            total = total + i
    return total