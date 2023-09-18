class Point: 
    def __init__(self, x:int, y:int): 
        # 포인트 초기화 메소드
        self.x = x
        self.y = y
        

class LineSegment:
    def __init__(self, point1:Point, point2:Point):
        # 선분의 시작점과 끝점 초기화 메소드
        self.startpoint = point1
        self.endpoint = point2
        
    def slope(self):
        # 선분의 기울기를 계산하는 메소드
        x_inc = self.endpoint.x - self.startpoint.x  # x 좌표의 증가량
        y_inc = self.endpoint.y - self.startpoint.y  # y 좌표의 증가량
        return y_inc / x_inc  # 기울기 반환
    
    def length(self):
        # 선분의 길이를 계산하는 메소드
        from math import sqrt
        x_inc = self.endpoint.x - self.startpoint.x  # x 좌표의 증가량
        y_inc = self.endpoint.y - self.startpoint.y  # y 좌표의 증가량
        return sqrt((x_inc**2) + (y_inc**2))  # 길이 반환


if __name__ == "__main__":
    # 예제 코드
    segment = LineSegment(Point(1,1), Point(3,2))
    print(segment.slope())  # 선분의 기울기 출력
    print(segment.length())  # 선분의 길이 출력
