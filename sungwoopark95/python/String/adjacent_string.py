def foo(s:str) :
    #step1) 문자별로 인접한 단어를 확인할 수 있는 dictionary를 만든다. adjacent_dict
    #step2) 모든 문자별 개수를 확인할 수 있는 dictionary를 만든다. word_cnt_dict
    #step3) 조건을 만족하면서 배치가능한 character을 append해가며 답을 찾는다.
    #       직전까지 완성된 단어의 마지막글자를 고려하여, 다음글자로 올 수 있는 char set을 확인하고 해당 set을 기반으로 traversal loop를 돌린다.
    #       원래 str과 동일한 길이를 찾으면 return한다.
    #       모든 loop를 돌렸는데도 길이가 동일한 string을 찾지 못하면 ""를 return 한다.
    if s==None : return ""
    n=len(s)
    if n==1 : return s


    adjacent_dict={} #dictionary 단어(key)별로 인접하면 안 되는 단어 set(value)
    word_cnt={} # dictionary 단어(key)별 단어개수(value)
    all_character=set() #단어 모두 모아놓은 곳
    for i, c in enumerate(s) :
        all_character.add(c)
        if c in word_cnt.keys():
            word_cnt[c]+=1
        else :
            word_cnt[c]=1
        if c not in adjacent_dict.keys() :
            adjacent_dict[c]=set()
        if i>0 :
            adjacent_dict[s[i-1]].add(c) #앞글자의 adjacent list에 현재 글자 담기
            adjacent_dict[c].add(s[i-1]) #현재글자의 adjacent list에 직전글자 담기

    #디버깅용 프린트
    # print(adjacent_dict)
    # print(word_cnt)
    # print(all_character)
    

    def _help_find(ans:str, word_left:dict) :
        '''ans:현재까지 작성된 글자, word_left:남아있는 글자수 정보'''
        if len(ans)==n : return ans #길이가 같으면 반환
        if len(ans) > 0 : #작성중이었다면
            prev_char=ans[-1] #직전글자 확인
            banned_char=adjacent_dict[prev_char] #인접하면안되는 단어들 확인
            possible_char=all_character-banned_char #다음글자로 올수있는 단어 set 구성(차집합)
            for curr_char in possible_char : #사용가능한 단어에 대해서 모두 for-loop
                if word_left[curr_char] >0 : #단어가 남아있다면
                    new_word_left=word_left.copy() #dictionary copy(copy하지 않고 함수 argument로 집어넣으려면 recursive call 중에 변해버려서 다시 못 씀)
                    new_ans=ans+curr_char #단어 추가후
                    new_word_left[curr_char]-=1 #개수 조정하고
                    # print(f"current ans is {new_ans}") #디버깅용
                    ans=_help_find(new_ans, new_word_left) #recursive call에서 답을 찾아온뒤
                    if len(ans)==n : return ans #답이 있다면 return해
            del word_left # loop 다 돌고나서는 이미 copy된 dictionary이므로 불필요하니 지운다.
            return ""
        else : #len(ans)==0 첫시작
            for c in all_character :
                new_ans=c
                new_word_left=word_left.copy()
                new_word_left[c]-=1 #개수 조정하고
                ans=_help_find(new_ans, new_word_left)
                if len(ans)==n : return ans
            del word_left
            return ""

    return _help_find("", word_cnt)

ans=foo('abccde')
display(ans)
ans=foo(' ')
display(ans)
        