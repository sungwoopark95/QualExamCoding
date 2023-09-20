
/*
# 841. Keys and Rooms
Solved
Medium
Topics
Companies
There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.

When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.

Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.

 

Example 1:

Input: rooms = [[1],[2],[3],[]]
Output: true
Explanation: 
We visit room 0 and pick up key 1.
We then visit room 1 and pick up key 2.
We then visit room 2 and pick up key 3.
We then visit room 3.
Since we were able to visit every room, we return true.
Example 2:

Input: rooms = [[1,3],[3,0,1],[2],[0]]
Output: false
Explanation: We can not enter room number 2 since the only key that unlocks it is in that room.
 

Constraints:

n == rooms.length
2 <= n <= 1000
0 <= rooms[i].length <= 1000
1 <= sum(rooms[i].length) <= 3000
0 <= rooms[i][j] < n
All the values of rooms[i] are unique.
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize){
    int* visited = (int*)calloc(roomsSize, sizeof(int));
    int cnt=0;
    //define dfs function
    void help_dfs(int idx) {
        if (visited[idx]){return;}
        visited[idx]=1;
        cnt++;
        int new_idx;
        for (int i=0; i<roomsColSize[idx];i++){
            new_idx=rooms[idx][i];
            help_dfs(new_idx);
        }
    }

    help_dfs(0);
    return (cnt==roomsSize);
}

// First try

// typedef struct {
//     int* element;
//     int size;
//     int capacity;
// } Set;

// void init_set(Set* set, int capacity) {
//     set->capacity=capacity;
//     set->size=0;
//     set->element=(int*)malloc(capacity*sizeof(int));
// }

// bool contains(Set *set, int value) {
//     for (int i = 0; i < set->size; i++) {
//         if (set->element[i] == value) {
//             return true;
//         }
//     }
//     return false;
// }

// void add(Set *set, int value) {
//     if (!contains(set, value)) {
//         set->element[set->size++] = value;
//     }
// }


// bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize){
//     Set visited;
//     init_set(&visited, 1000);

//     //define dfs function
//     void help_dfs(int idx) {
//         if (contains(&visited, idx)){return;}
//         add(&visited, idx);
//         int new_idx;
//         for (int i=0; i<roomsColSize[idx];i++){
//             new_idx=rooms[idx][i];
//             help_dfs(new_idx);
//         }
//     }

//     help_dfs(0);
//     return (visited.size==roomsSize);
// }