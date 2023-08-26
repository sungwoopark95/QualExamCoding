"""
(a) `__init__`메소드를 사용하여 2개의 인자(`name`, `countries`)를 가진 `Continent` 클래스를 정의해 보아라. 
    * `countries`는 `Country` class의 객체들로 이루어진 list이다. 
    * `countries` list가 비어있는 경우는 고려하지 않는다. 

(b) `Continent` 클래스의 메소드인 `total_population`을 구현하여라 
    * `total_poulation` 메소드는 대륙에 속한 국가들의 인구의 합을 반환하는 메소드이다.
"""

from typing import List
from Country import Country

class Continent:
    def __init__(self, name:str, countries:List[Country]):
        self.name = name
        self.countries = countries
        
    def total_population(self):
        return sum([country.population for country in self.countries])
    
if __name__ == "__main__":
    canada = Country('Canada', 34482779, 9984670)
    usa = Country('United States of America', 313914040, 9826675)
    mexico = Country('Mexico', 112336538, 1943950) 
    countries = [canada, usa, mexico] 

    north_america = Continent('North America', countries) 
    print(north_america.name)
    print(north_america.total_population())
    