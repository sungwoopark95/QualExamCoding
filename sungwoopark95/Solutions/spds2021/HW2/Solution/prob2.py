from prob1 import Spreadsheet

class PermanentSpreadsheet(Spreadsheet):
    """
    Permanent Spreadsheet is a Spreadsheet where it allows exporting current
    status and allows importing later
    
    Permanent Spreadsheet is a child class of Spreadsheet with two more method:
        export_sheet(filename) and import_sheet(filename)
    
    Export_sheet will save the current status of file into filename.
    Filename must be a string object, and if not must throw type error
    
    Import_sheet will clear all element and recall file saved from filename
    """
    
    def export_sheet(self, filename):
        # Helper function convert which will convert the row col to the spreadsheet index
        def convert(row, col):
            index = ""
            if col == 0:
                index = 'a' + str(row + 1)
            elif col == 1:
                index = 'b' + str(row + 1)
            elif col == 2:
                index = 'c' + str(row + 1)
            elif col == 3:
                index = 'd' + str(row + 1)
            elif col == 4:
                index = 'e' + str(row + 1)
            elif col == 5:
                index = 'f' + str(row + 1)
            elif col == 6:
                index = 'g' + str(row + 1)
            elif col == 7:
                index = 'h' + str(row + 1)
            elif col == 8:
                index = 'i' + str(row + 1)
            else:
                index = 'j' + str(row + 1)   
            return index
        
        # Check if the filename is string
        if type(filename) == str:
            
            # Build content for the filename
            content = ""
            row_count = 0
            # Iterate through the spreadsheet
            for i in self.sheet:
                # save the object in the format 
                col_count = 0
                for j in i:
                    # Check the datatype
                    if type(j) == int:
                        content = content + str(convert(row_count,col_count)) + "," + str(j) + ",int\n"
                    elif type(j) == str:
                        content = content + str(convert(row_count,col_count)) + "," + str(j) + ",str\n"
                    elif type(j) == bool:
                        content = content + str(convert(row_count,col_count)) + "," + str(j) + ",bool\n"
                    else:
                        content = content + str(convert(row_count,col_count)) + "," + str(j) + ",None\n"
                    
                    col_count = col_count + 1
                
                row_count = row_count + 1
                    
            # open the file
            f = open(filename, 'w')
            # write its content
            f.write(content)
            # close the file
            f.close()
        # if not string throw Type Error
        else:
            raise TypeError('Filename only accepts string')
    
    def import_sheet(self, filename):
        # Check if the filename is string
        if type(filename) == str:
            # open file
            f = open(filename, 'r')
            # Initialize row number
            num = 0
            
            # go through line by line and save the value index by index
            for line in f:
                # strip off \n then split the line by comma
                # Fill up the spreadsheet using the set value
                line = line.strip().split(",")
                if line[2] == 'int':
                    self.set_value(line[0], int(line[1]))
                elif line[2] == 'str':
                    self.set_value(line[0], str(line[1]))
                elif line[2] == 'bool':
                    self.set_value(line[0], bool(line[1]))
                else:
                    pass
            # close file
            f.close()
        # if not string throw Type Error
        else:
            raise TypeError('Filename only accepts string')