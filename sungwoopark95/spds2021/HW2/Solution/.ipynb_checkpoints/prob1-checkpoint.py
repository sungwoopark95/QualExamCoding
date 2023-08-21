class Spreadsheet:
    """
    Spreadsheet is like a Microsoft Excel where it can read and save the data.
    It has following criteria
    - It is 10 x 10 index where row goes from 1 - 10 and col goes from alphabet
        a-j or A-j
    - For each cell in a spreadsheet, it can only take integer, boolean, and string.
        Furthermore, for strin, we assume there are no whitespace
    - Creater does not take other input (?)
    - When Spreadsheet is printed, it should be seperated by comma
        and each row should be separated by new line character.
    - Spreadsheet takes in two method = get_value and set_value
    """
    #Constructor will create an empty 10 x 10 array
    def __init__(self):
        self.sheet = [[None for i in range(10)] for j in range(10)]
    
    #Make the String to be in the designated format
    def __str__(self):
        # Initialize a string table
        table = ""
        # Initialize a counter so that it will not add new line for last line
        count = 0
        # Iterate through for loop to go through all the matrix
        for i in self.sheet:
            # Initialize a counter count to make sure the matrix
            # is printed as 10 x 10
            count2 = 0
            # Iterate through each row
            for j in i:
                # Add the , if not end of the string
                if count2 < len(i) - 1:
                    if j == None:
                        table = table + " , "
                    else:
                        table = table + str(j) +" , "
                # Add newline character if end of the column
                else:
                    if count < len(self.sheet) - 1:
                        if j == None:
                            table = table + " \n"
                        else:
                            table = table + str(j) + " \n"
                    # If it is last row, newline character will not be added
                    else:
                        if j == None:
                            table = table + " "
                        else:
                            table = table + str(j) + " "
                count2 = count2 + 1
            count = count  +1
        return table
    
    # obtain value from the sheet
    def get_value(self, idx):
        # Check if the index is string
        if type(idx) == str:
            
            # Note the index must be 2-3 letter
            if len(idx) < 2:
                raise IndexError("Invalid Index")
            
            # initialize row i and column j
            i = 0
            j = 0
            # convert index to be lower case so that it will accpet
            # both uppercase and lower case
            idx = idx.lower()
            
            # Sepearate index into row and column number
            col = idx[0]
            row = idx[1:]
            
            # convert the row index to be ranging from 0 - 9 
            # instead of 1 - 10
            # Because int operation will take Value Error and
            # our assignment requires Index Error convert the type
            # if it is in incorrect format
            try:
                row = int(row) - 1
            except ValueError:
                raise IndexError("Invalid Index") from None
                
            # Making sure if the value is from 0 - 9
            if (row > 9 or row < 0):
                raise IndexError("Invalid Index")
            
            # Now i will be the row value
            i = row
            
            # Now convert the column index to be a number
            if col == 'a':
                j = 0
            elif col == 'b':
                j = 1
            elif col == 'c':
                j = 2
            elif col == 'd':
                j = 3
            elif col == 'e':
                j = 4
            elif col == 'f':
                j = 5
            elif col == 'g':
                j = 6
            elif col == 'h':
                j = 7
            elif col == 'i':
                j = 8
            elif col == 'j':
                j = 9
            else:
                raise IndexError("Invalid Index")
            
            return self.sheet[i][j]
            
        # if not string throw Type Error
        else:
            raise TypeError('idx only accepts string')
    
    # set value for the sheet
    def set_value(self, idx, value):
        # Copy the code directly from get_value
        # Check if the index is string
        if type(idx) == str:
            
            # Note the index must be 2-3 letter
            if len(idx) < 2:
                raise IndexError("Invalid Index")
            
            # initialize row i and column j
            i = 0
            j = 0
            # convert index to be lower case so that it will accpet
            # both uppercase and lower case
            idx = idx.lower()
            
            # Sepearate index into row and column number
            col = idx[0]
            row = idx[1:]
            
            # convert the row index to be ranging from 0 - 9 
            # instead of 1 - 10
            # Because int operation will take Value Error and
            # our assignment requires Index Error convert the type
            # if it is in incorrect format
            try:
                row = int(row) - 1
            except ValueError:
                raise IndexError("Invalid Index") from None
                
            # Making sure if the value is from 0 - 9
            if (row > 9 or row < 0):
                raise IndexError("Invalid Index")
            
            # Now i will be the row value
            i = row
            
            # Now convert the column index to be a number
            if col == 'a':
                j = 0
            elif col == 'b':
                j = 1
            elif col == 'c':
                j = 2
            elif col == 'd':
                j = 3
            elif col == 'e':
                j = 4
            elif col == 'f':
                j = 5
            elif col == 'g':
                j = 6
            elif col == 'h':
                j = 7
            elif col == 'i':
                j = 8
            elif col == 'j':
                j = 9
            else:
                raise IndexError("Invalid Index")
            
            # Now, we have to check the type for the value is int, str, or boolean
            # If so, set the value to be value.
            # Else, throw type error
            if ((type(value) == str) or (type(value) == int) or (type(value) == bool)):
                self.sheet[i][j] = value
            else:
                raise TypeError('value must be string, boolean, or integer')
            
            
        # if not string throw Type Error
        else:
            raise TypeError('idx only accepts string')