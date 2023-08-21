from prob1 import Spreadsheet

class SmartSpreadsheet(Spreadsheet):
    """
    SmartSpreadsheet is a child class of SpreadSheet. Smart Spreadsheet has a method where a lambda function can be applied from one cell
    to the other. The function that is new from Spreadsheet class is set_function. The following function takes in three input idx, function,
    and operand_idx. Similar to Excel, if the value of the dependent cell the value of operand index must also change. Operand index may
    also dependent on other operand index. However, operand index may not cross over with the reference index.
    """
    # Create a global variable so that it can be used to update the value
    operand = []

    #def set_function(self, idx, function, operand_idx):
        #self.set_value(idx, function(self.get_value(operand_idx)))
    
    def set_function(self, idx, function, operand_idx):
        # Set a index to be lambda value of the other index
        self.set_value(idx, function(self.get_value(operand_idx)))
        # Save the function, operand and index if it is not in update
        if [operand_idx, function, idx] not in SmartSpreadsheet.operand:
            SmartSpreadsheet.operand.append([operand_idx, function, idx])
        
    def set_value(self, idx, value):
        # Retrieve all function from the original class
        super().set_value(idx,value)
        
        # Update the value if it is like it
        for i in range(len(SmartSpreadsheet.operand)):
            # Check if index matches
            if SmartSpreadsheet.operand[i][0] == idx:
                # update if so
                self.set_function(SmartSpreadsheet.operand[i][2],SmartSpreadsheet.operand[i][1],SmartSpreadsheet.operand[i][0])