/*
[유효한 괄호 찾기]
‘(‘, ‘)’, ‘{‘, ‘}’, ‘[‘, ‘]’으로 구성된 String을 Input으로 받고, 
이 String이 아래 규칙에 의해 유효한지를 판단하여 True/False를 return하는 함수를 작성하여라.

<조건>
(1) 괄호가 열렸다면 같은 타입의 괄호에 의해 닫혀야 한다.
(2) 적절한 순서로 괄호가 배열되어야 한다. 안쪽에서 열린 괄호가 먼저 닫히고, 바깥쪽 괄호가 닫혀야 한다.

TestCase2)
>>> P1(‘()[]{}’) True
TestCase3)
>>> P1(‘([)]’) False
*/

#include <map>
#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    bool isValid(string s) {
        
        map<char, char> mapping;
        mapping['['] = ']';
        mapping['('] = ')';
        mapping['{'] = '}';
        
        vector<char> queue;
        
        for (int i=0; i<s.length(); i++) {
            if (mapping[s[i]]) {
                queue.push_back(s[i]);
            } else {
                if (queue.size() == 0) {
                    return false;
                } else {
                    char curr = queue.back();
                    queue.pop_back();
                    if (mapping[curr] != s[i]) {
                        return false;
                    }
                }
            }
        }
        
        if (queue.size() != 0) {
            return false;
        } return true;
    }
};

int main() {
    Solution* Sol = new Solution();

    string s = "()";
    cout << Sol->isValid(s) << endl;
}

// map = {
//     "[" : "]",
//     "(" : ")",
//     "{" : "}"
//     }

// queue = list()

// for i in range(len(s)):
//     if s[i] in map:
//         queue.append(s[i])
//     else:
//         if not queue: 
//             return False
//         else:
//             curr = queue.pop()
//             if map[curr] != s[i]:
//                 return False

// if len(queue) == 0:
//     return True