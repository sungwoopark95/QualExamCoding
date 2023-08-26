"""
(a) `LineSegment` 클래스의 메소드인 `slope` 메소드는 선분의 기울기를 반환하는 메소드이다. `slope` 메소드를 구현해 보아라. 
    * 선분이 y축과 평행한 경우의 `slope`는 고려하지 않아도 된다.
    
(b) `LineSegment` 클래스의 메소드인 `length` 메소드는 선분의 길이를 반환하는 메소드이다. `length` 메소드를 구현해 보아라. 
"""

class Point: 
    def __init__(self, x:int, y:int): 
        self.x = x
        self.y = y
        

class LineSegment:
    def __init__(self, point1:Point, point2:Point):
        self.startpoint = point1
        self.endpoint = point2
        
    def slope(self):
        x_inc = self.endpoint.x - self.startpoint.x
        y_inc = self.endpoint.y - self.startpoint.y
        return y_inc / x_inc
    
    def length(self):
        from math import sqrt
        x_inc = self.endpoint.x - self.startpoint.x
        y_inc = self.endpoint.y - self.startpoint.y
        return sqrt((x_inc**2) + (y_inc**2))


if __name__ == "__main__":
    segment = LineSegment(Point(1,1), Point(3,2))
    print(segment.slope())
    print(segment.length())
