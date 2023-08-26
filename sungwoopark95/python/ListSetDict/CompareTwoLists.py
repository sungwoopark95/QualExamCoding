from typing import List

def P10(rat_1:List, rat_2:List, day:int):
    return rat_1[day-1] > rat_2[day-1]

if __name__ == "__main__":
    rat_1 = [5, 6, 7, 6, 7, 8, 10, 9, 8, 10]
    rat_2 = [7, 8, 6, 7, 8, 10, 9, 8, 10, 11]
    
    print(P10(rat_1, rat_2, 1))
    print(P10(rat_1, rat_2, 5))
