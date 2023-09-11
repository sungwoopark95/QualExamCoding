#include <stdio.h>
#include <stdlib.h>
//include "ArrayList/ArrayList.hpp"
#include "./singly_linked_list.hpp"
//#include "CircularLinkedList/CircularLinkedList.hpp"
//include "DoublyLinkedList/DoublyLinkedList.hpp"

using namespace std;

class Point {
private:
    int x;  // x 좌표
    int y;  // y 좌표
    
public:
    // 기본 생성자: (0,0)으로 초기화
    Point() {
        x = 0;
        y = 0;
    }
    // 매개변수 있는 생성자: 주어진 좌표로 초기화
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    // 소멸자
    ~Point() {
    }
    // Point 객체의 좌표 출력 함수
    void print(void) {
        printf("(%d, %d)\n",x, y);
    }
    // 두 Point 객체가 같은지 확인하는 연산자 오버로딩
    bool operator==(Point& reference) {
        return (x == reference.x) && (y == reference.y);
    }
};

// ArrayList를 사용할 때의 typedef
// typedef ArrayList<Point*> List;
// LinkedList를 사용하는 경우의 typedef
typedef LinkedList<Point*> List;

int main(int argc, char** argv) {
    List list;  // Point 포인터들의 리스트 생성
    
    srand(time(NULL));
    // 10개의 랜덤 Point 객체를 리스트에 추가
    for(int i = 0; i < 10; i++) {
        list.add(new Point(rand()%3, rand()%3));
    }
    
    /* 데이터 출력 */
    printf("현재 데이터 수: %d\n", list.getSize());
    
    (list.first())->print();  // 첫 번째 Point 출력
    // 나머지 Point들 출력
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        (list.next())->print();
    }
    printf("---printf finished--\n");
    
    /* 데이터 삭제 */
    // 랜덤한 Point 생성하여 해당 좌표를 가진 Point 삭제
    Point* comparePosition = new Point(rand()%3, rand()%3);
    printf("삭제할 Point: ");
    comparePosition->print();
    
    // 첫 번째 Point 비교 및 삭제
    if(*(list.first()) == *comparePosition) {
        delete(list.remove());
    }
    // 나머지 Point들 비교 및 삭제
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        if(*(list.next()) == *comparePosition) {
            delete(list.remove());
        }
    }
    delete(comparePosition);
    
    /* 데이터 출력 */
    printf("현재 데이터 수: %d\n", list.getSize());
    
    (list.first())->print();  // 첫 번째 Point 출력
    // 나머지 Point들 출력
    for(int i = 0; (i<list.getSize() - 1) && (list.hasNext()); i++) {
        (list.next())->print();
    }
    printf("---printf finished--\n");
    
    // 메모리 정리: 리스트에 남아있는 모든 Point들 삭제
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
