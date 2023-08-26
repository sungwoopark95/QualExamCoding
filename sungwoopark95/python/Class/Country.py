"""
(a) `__init__` 메소드를 사용하여 3개의 인자(`name`, `population`, `area`)를 가진 `Country` 클래스를 정의 해 보아라

(b) `Country` 클래스의 메소드인 `is_larger`를 정의해 보아라. 
* `is_larger` 메소드는 첫 번째 국가가 두 번째 국가에 비해 더 큰 면적을 지녔을 때에만 `True`를 반환하는 메소드이다. (면적이 같을 경우 `False` 반환) 

(c) `Country` 클래스의 메소드인 `population_density`를 정의해 보아라. 
* `population_density` 메소드는 국가의 인구 밀도 (면적 당 인구 수)를 반환하는 메소드이다. (`area`가 0인 경우는 없다.) 
"""
from __future__ import annotations # 19번째줄 warning 처리하기 위함
from typing import List

class Country:
    def __init__(self, name:str, population:int, area:int):
        self.name = name
        self.population = population
        self.area = area
    
    def is_larger(self, c:Country):
        return self.area > c.area
    
    def population_density(self):
        return self.population / self.area
    
if __name__ == "__main__":
    canada = Country('Canada', 34482779, 9984670)
    usa = Country('United States of America', 313914040, 9826675)
    print(canada.is_larger(usa))
    print(canada.population_density())
