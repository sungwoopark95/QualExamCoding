"""
# P4

일련의 실험을 수행한 후, 특정 다섯 종류의 아원자 입자(subatomic particles)를 탐지할 확률을 {str: float} 딕셔너리 형태로 다음과 같이 저장했다.
{'neutron': 0.55, ‘proton': 0.21, 'meson': 0.03, 'muon': 0.07, 'neutrino': 0.14}
이러한 딕셔너리를 변수(argument)로 받아 탐지 가능성이 가장 큰 입자를 리턴하는 함수를 작성하시오. 

<조건>
1. 입자가 발견될 확률이 같은 경우는 없음

예시1) 
```
>>> P4({'neutron': 0.55, 'proton': 0.21, 'meson': 0.03, 'muon': 0.07, 'neutrino': 0.14})
'neutron'
```

예시2)
```
>>> P4({'neutron': 0.11, 'proton': 0.21, 'meson': 0.05, 'muon': 0.09, 'neutrino': 0.12})
'proton'
```
"""

from typing import Dict

def P4(particles:Dict[str, float]):
    max_particle = ""
    max_prob = 0.
    for name, prob in particles.items():
        if prob > max_prob:
            max_prob = prob
            max_particle = name
    return max_particle

if __name__ == "__main__":
    print(P4({'neutron': 0.55, 'proton': 0.21, 'meson': 0.03, 'muon': 0.07, 'neutrino': 0.14}))
    print(P4({'neutron': 0.11, 'proton': 0.21, 'meson': 0.05, 'muon': 0.09, 'neutrino': 0.12}))
