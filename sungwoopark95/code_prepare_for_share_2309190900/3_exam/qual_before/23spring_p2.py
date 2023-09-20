class Node :
    def __init__(self, data, next) :
        self.data = data
        self.next = next

def print_list(s: Node) :
    return

def palindrome(s:Node) :
    '''return 1 if palindrome else 0'''
    if s==None : return 1
    length=0
    curr=s
    val_list=[]
    while curr!=None :
        length+=1
        val_list.append(curr.data)
        curr=curr.next
    
    rear_pointer=length//2
    front_pointer=rear_pointer-1
    if length%2==0 : rear_pointer+=1
    while (front_pointer>=0) :
        if val_list[front_pointer]!=val_list[rear_pointer] : 
            return 0
        front_pointer-=1
        rear_pointer+=1
    return 1

def sub_list(s:Node, t:Node) :

    ptr1=s
    ptr2=t
    