#include <stdio.h>
#include <stdlib.h>
//include "ArrayList/ArrayList.hpp"
#include "./singly_linked_list.hpp"
//#include "CircularLinkedList/CircularLinkedList.hpp"
//include "DoublyLinkedList/DoublyLinkedList.hpp"

using namespace std;

class Point {
private:
    int x;
    int y;
    
public:
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    ~Point() {
    }
    void print(void) {
        printf("(%d, %d)\n",x, y);
    }
    bool operator==(Point& reference) {
        return (x == reference.x) && (y == reference.y);
    }
};

// typedef ArrayList<Point*> List;
typedef LinkedList<Point*> List;

int main(int argc, char** argv) {
    List list;
    
    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        list.add(new Point(rand()%3, rand()%3));
    }
    
    /* 데이터 출력 */
    printf("현재 데이터 수: %d\n", list.getSize());
    
    (list.first())->print();
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        (list.next())->print();
    }
    printf("---printf finished--\n");
    
    /* 데이터 삭제 */
    Point* comparePosition = new Point(rand()%3, rand()%3);
    printf("삭제할 Point: ");
    comparePosition->print();
    
    if(*(list.first()) == *comparePosition) {
        delete(list.remove());
    }
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        if(*(list.next()) == *comparePosition) {
            delete(list.remove());
        }
    }
    delete(comparePosition);
    
    /* 데이터 출력 */
    printf("현재 데이터 수: %d\n", list.getSize());
    
    (list.first())->print();
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        (list.next())->print();
    }
    printf("---printf finished--\n");
    
    // 메모리 정리
    if(!list.isEmpty()) {
        list.first();
        delete(list.remove());
        
        for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
            list.next();
            delete(list.remove());
        }
    }
    
    return 0;
}