# QualExamCoding

## 🪜 스터디원 명단 및 `dir 이름`

1. 박성우 `sungwoopark95`
2. 김성문 `soungmunkim`



## :warning: 주의사항

- 모든 문제를 `Python`, `C`, `C++`로 한 번씩 풀어보기! (가능하다면)



## :calendar: Weekly Timetable (to be updated)

|                주차                 |                             내용                             |                             링크                             |
| :---------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| Week1 <br> 2023-08-07 - 2023-08-13  |                  컴기 숙제 한 번씩 풀어보기                  |                                                              |
|       Week2<br /> 2023-08-14        |               2022 & 2023 논자시 기출 풀어보기               |                                                              |
| Week2<br /> 2023-08-15 - 2023-08-20 |       컴1 과제 & 알고리즘 각 언어로 한 번씩 구현해보기       |                                                              |
| Week3<br /> 2023-08-21 - 2023-08-27 |      2021 컴퓨팅 수업때 다뤘던 과제들 훑어보고 풀어보기      |                                                              |
| Week4<br /> 2023-08-28 - 2023-09-03 | 컴기 & 논자시 기출 바탕으로 리트코드 or 백준 문제집 하나 정해서 풀기<br /> or 여태까지 했던 것들 복습 | <a href="https://www.youtube.com/watch?v=LcOIobH7ues&list=PLtqbFd2VIQv4O6D6l9HcD732hdrnYb6CY" target="_blank">바킹독 강의</a><br /><a href="https://github.com/encrypted-def/basic-algo-lecture" target="_blank">바킹독 문제집</a><br /><a href="https://leetcode.com/problemset/all/" target="_blank">Leetcode</a> |
| Week5<br /> 2023-09-04 - 2023-09-10 |                                                              |                                                              |
| Week5<br /> 2023-09-11 - 2023-09-17 |         :exclamation: **최 종 정 리** :exclamation:          |                                                              |

## :spiral_notepad: Progress Updates (to be updated)

|                              Tasks                              |          성우           |           성문          |
|:--------------------------------------------------------------: | :--------------------: | :--------------------: |
|       HW3 - HW6 <br> `Python` 기초 ~ File I/O in `Python`        |   :white_check_mark:   |   :white_check_mark:   |
|  HW7, HW14, HW17, HW19 <br> `Python` 응용, `C` 기초 및 string 처리  |   :white_check_mark:   |   :white_check_mark:   |
| HW8, HW9 <br> Sorting, Stack, Queue, and Linked List (`Python`) |   :white_check_mark:   |   :white_check_mark:   |
|               HW10, HW11 <br> BFS & DFS (`Python`)              |   :white_check_mark:   |   :white_check_mark:   |
|      HW12, HW18 <br> Hashing (`Python`) & 수학 알고리즘 (`C`)      |   :white_check_mark:   |   :white_check_mark:   |
|            HW20, HW21 <br> File I/O in `C` & `C` 응용            |   :white_check_mark:   |   :white_check_mark:   |
|    HW1, HW2 SPDS(2021년도) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        | HW :white_check_mark: <br /> (HW2 C++ <br /> 실패) |
|    HW3, HW4 SPDS(2021년도) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        | HW :white_check_mark:  |
|    HW5, HW6 SPDS(2021년도) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        |                         |
|    HW1, HW2 (2022년 1학기) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        | HW :white_check_mark:  |
|    HW3, HW4 (2022년 1학기) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        |  HW :white_check_mark: |
|    HW5 (1학기), HW1 (2학기) C/C++ <br /> 알고리즘 1개 각 언어로 구현    |                        |  HW :white_check_mark: |
|          HW2 (2학기) C/C++ <br /> 알고리즘 1개 각 언어로 구현          |                        |  HW :white_check_mark:  |
|                      2022 & 2023 논자시 기출                      |                        |                         |

### 주요 용어

* 원격 repository: 코드들 올려놓은 github 페이지 (그냥 우리가 보는 깃헙 페이지라고 생각하면 됨)
* 로컬 repository: 로컬(및 서버) 등에 위치한 작업공간 (로컬에 있는 폴더라고 생각하면 됨)
* Pull: 원격 repository의 내용을 로컬 repository로 가져오는 작업
* Push: 로컬 repository에 새롭게 업데이트한 내용을 원격 repository에 업로드하는 작업

### 주요 커맨드 (터미널 창에 치면 됨)

- 우선 `cd` 사용해서 로컬 repository로 이동

- 모든 작업을 시작하기 전이나 원격 repository에 업로드 하기 전에 :exclamation:**항상** **pull해주는 습관**:exclamation: 들이기!

  - 그래야 충돌이 나지 않고 안전하게 업로드할 수 있음
  - pull command: `git pull origin main`

- :exclamation:**Push하는 과정 (2번 빼고는 생략하면 안 됨!)**:exclamation:

  1. `git add .` : 로컬 repository에 새롭게 저장한 내용 추가
  2. `git status` : add한 내용들이 제대로 잘 반영됐는지, 어떤 변동사항이 생기는지 체크 **(생략해도 괜찮음)**
  3. `git commit -m "commit message"` : add한 내용을 최종 확인하고, 어떤 변동사항이 있었는지를 message의 형태로 적는 작업
  4. `git push origin main` : 최종 확인한 update를 원격 repository에 덮어쓰는 작업

- Git Conflict가 나서 이전의 내용으로 다시 덮어쓰고 싶을 때

  ```sh
  git fetch --all
  git reset --hard origin/main
  git pull origin main

* 정 안되면 그냥 로컬 repository 삭제하고 다시 `git clone`해도 괜찮음
