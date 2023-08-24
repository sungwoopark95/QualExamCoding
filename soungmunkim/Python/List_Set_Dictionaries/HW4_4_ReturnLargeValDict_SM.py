"""
일련의 실험을 수행한 후, 
특정 다섯 종류의 아원자 입자(subatomic particles)를 탐지할 확률을 딕셔너리 형태로 다음과 같이 저장했다.
{'neutron': 0.55, ‘proton': 0.21, 'meson': 0.03, 'muon': 0.07, 'neutrino': 0.14} 
이러한 딕셔너리를 변수(argument)로 받아 탐지 가능성이 가장 큰 입자를 리턴하는 함수를 작성하시오.

TestCase1)
>>> P4({'neutron': 0.55, 'proton': 0.21, 'meson': 0.03, 'muon': 0.07, 'neutrino': 0.14}) 
'neutron'
"""
def P4(dic):
    max_val = max(dic.values())
    for k,v in dic.items():
        if v == max_val:
            return k