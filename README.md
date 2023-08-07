# QualExamCoding

## 🪜 스터디원 명단 및 `dir 이름`

1. 박성우 `sungwoopark95`
2. 김성문 `sungmoonie`



## :warning: 주의사항

- 모든 문제를 `Python`, `C`, `C++`로 한 번씩 풀어보기! (가능하다면)



## :calendar: Weekly Timetable (to be updated)

|                주차                 |                             내용                             |                             링크                             |
| :---------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| Week1 <br> 2023-08-07 ~ 2023-08-13  |                  컴기 숙제 한 번씩 풀어보기                  |                                                              |
|       Week2<br /> 2023-08-14        |               2022 & 2023 논자시 기출 풀어보기               |                                                              |
| Week2<br /> 2023-08-15 ~ 2023-08-20 | 컴기 & 논자시 기출 바탕으로 리트코드 or 백준 문제집 하나 정해서 풀기 | <a href="https://www.youtube.com/watch?v=LcOIobH7ues&list=PLtqbFd2VIQv4O6D6l9HcD732hdrnYb6CY" target="_blank">바킹독 강의</a><br /><a href="https://github.com/encrypted-def/basic-algo-lecture)" target="_blank">바킹독 문제집</a><br /><a href="https://leetcode.com/problemset/all/" target="_blank">Leetcode</a> |
| Week3<br /> 2023-08-21 ~ 2023-08-27 |                                                              |                                                              |
| Week4<br /> 2023-08-28 ~ 2023-09-03 |                                                              |                                                              |
| Week5<br /> 2023-09-04 ~ 2023-09-10 |                                                              |                                                              |
| Week5<br /> 2023-09-11 ~ 2023-09-17 |         :exclamation: **최 종 정 리** :exclamation:          |                                                              |



## :spiral_notepad: Daily Tasks (to be updated)

|    날짜    |          Tasks          |                   내용                   |
| :--------: | :---------------------: | :--------------------------------------: |
| 2023-08-08 |        HW3 - HW6        |   `Python` 기초 ~ File I/O in `Python`   |
| 2023-08-09 |  HW7, HW14, HW17, HW19  |  `Python` 응용, `C` 기초 및 string 처리  |
| 2023-08-10 |        HW8, HW9         |     Sorting & Linked List (`Python`)     |
| 2023-08-11 |       HW10, HW11        |           BFS & DFS (`Python`)           |
| 2023-08-12 |       HW12, HW18        | Hashing (`Python`) & 수학 알고리즘 (`C`) |
| 2023-08-13 |       HW20, HW21        |        File I/O in `C` & `C` 응용        |
| 2023-08-14 | 2022 & 2023 논자시 기출 |                                          |



## :keyboard: Github 주요 용어 & 커맨드

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
