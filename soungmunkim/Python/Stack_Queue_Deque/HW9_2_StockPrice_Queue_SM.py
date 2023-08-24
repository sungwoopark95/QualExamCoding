"""
[Input으로 일별 주가(list)를 받고, 이득을 보기 위해 기다려야 하는 최소 일수(list)를 return하는 함수]

날짜 10/7 10/8 10/9 10/10 10/11 10/12 10/13 10/14 
주가 500  600  700   300   100   400   800   500 
일수  1    1    4     2     1     1     0     0

위의 표를 보면
(1) 예지가 10/7에 주식을 산다면 1일 뒤인 10/8에 팔면 이득을 본다.
(2) 예지가 10/9에 주식을 산다면 4일 뒤인 10/13에 팔면 이득을 본다.
(3) 이득을 볼 수 없다면 0으로 작성하면 된다.

위 설명을 참고하여 Input으로 일별 주가(list)를 받고, 이득을 보기 위해 기다려야 하는 최소 일수(list)를 return하는 함수를 작성하여라.

TestCase1)
>>> P2([500, 600, 700, 300, 100, 400, 800, 500]) 
[1, 1, 4, 2, 1, 1, 0, 0]
"""

def P2(stock_price: list):        
    ##### Write your Code Here #####
    ans = []
    store = []

    cnt = 0
    copy = stock_price[:]


    while stock_price != []:
        # 횟수가 마지막 index까지 도달했는데 해당 stock값이 이후에 값보다 크거나 같을때
        # 현재 가격 이후에 오르는 가격이 없을 때 0 추가 + 현재 가격 끝났으니 빼기
        if cnt == (len(copy) - len(store)) -1  and stock_price[0] >= stock_price[cnt]:
            ans.append(0)
            store.append(stock_price.pop(0))
            cnt = 0 
        
        # 가격이 오른다면 올랐던 횟수 j를 결과에 추가하고 j 다시 reset 시킴 + 현재 가격 끝났으니 빼기
        elif stock_price[0] < stock_price[cnt]:

            ans.append(cnt)
            store.append(stock_price.pop(0))        
            cnt = 0

        # 가격 오른 것 만날때까지 계속 횟수 +1
        else:
            cnt += 1
                    
    return ans