def prime_factorizer(n):
    """ 
    prime_factorizer 함수 구현
    
    The program takes in a input: integer value.
    Program will output tuples of base-exponent pair in form of list in ascending order.
    
    Program will find all prime factors of an input number n.
    Then, the program will count number of occurrence of each prime.
    Then, the program will return the result in the expected format.
    """
    # Initialize the list, so that it will save all prime factors of the input
    prime = []
    # Set value of a number to be a smallest prime
    x = 2
    # Run while Loop until the value becomes 1
    while n > 1:
        # If module of a number is 0, it means number is factor
        while n % x == 0:
            prime.append(x)
            n = n / x 
        x = x + 1
    
    # Initialize result
    result = []
    
    # Run While loop if not empty  
    if len(prime) > 0:
        # Initialize value to be smallest prime
        x = 2
        # Run the while loop until the value is bigger than biggest prime number
        while x <= max(prime):
            # Count number of occurrence
            val = prime.count(x)
            # if the prime exist, append to result
            if val > 0:
                tup = (x, val)
                result.append(tup)
            x = x + 1
        

    return result