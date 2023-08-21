def find_word(s,word):
    """
    find_word 함수 구현
    The program takes in two inputs: sentence and word.
    If the word is in the string, it will output list of word location.
    
    Program will first make both inputs into lowercase so that it will allow case sensitivity.
    In terms of sentence, for we are given, sentence is divided by period,
    comma, and spaces, delimiters will be replaced by spaces.
    Then, sentence will be spliced into array by each word.
    
    Then, the program will run for loop to identify location of word in the sentence.
    """
    
    # Replace comma and period to be whitespace so that the only delimeter for split will be whitespace.
    # Make both word and sentence to take care of case-sensitivity
    # Split the sentence to be the list so that it will contain word by element/position
    s = s.replace("."," ").replace(","," ").lower().split()
    word = word.lower()
    
    # Intialize result
    result =[]
    # Initialize count variable to find the location of the word in sentence
    count = 0

    # Iterate through for loop to check the word in sentence
    for i in s:
        # if the word is in the for loop, add the element to the list
        if i == word:
            result.append(count)
        count = count + 1
  
    return result