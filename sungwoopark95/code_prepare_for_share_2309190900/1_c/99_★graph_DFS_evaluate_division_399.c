
/*
You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
note: x is undefined => -1.0
Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]
Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]
 

Constraints:

1 <= equations.length <= 20
equations[i].length == 2
1 <= Ai.length, Bi.length <= 5
values.length == equations.length
0.0 < values[i] <= 20.0
1 <= queries.length <= 20
queries[i].length == 2
1 <= Cj.length, Dj.length <= 5
Ai, Bi, Cj, Dj consist of lower case English letters and digits.
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_VAR_LEN 6
#define MAX_VAR_NUM 40
#define MAX_EQ_NUM 20


/*"SET" for visited nodes*/
struct StringSet {
    char elements[MAX_VAR_NUM][MAX_VAR_LEN];
    int size;
};

void init_stringset(struct StringSet *ss){
    ss->size=0;
}

bool contains(struct StringSet *ss, const char *ele){
    for (int i=0; i<ss->size; i++){
        if (strcmp(ss->elements[i], ele)==0) {return true;}
    }
    return false;
}

void addString(struct StringSet *ss, const char *ele){
    if ( !contains(ss, ele) ){
        if (ss->size < MAX_VAR_NUM) {
            strcpy(ss->elements[ss->size], ele);
            ss->size++;
        }
        else {
            printf("ERROR.(Set is Full)\n");
        }
    }
}


/*"dictionary" for equation index*/
struct Dictionary {
    char keys[MAX_VAR_NUM][MAX_VAR_LEN];
    int indices[MAX_VAR_NUM][MAX_EQ_NUM];
    int num_keys;
    int num_idx[MAX_VAR_NUM];
};

void init_dictionary(struct Dictionary *d){
    d->num_keys=0;
    memset(d->num_idx, 0, sizeof(d->num_idx));
}


//return key_idx (if not exists, return -1)
int key_idx(struct Dictionary *d, const char *key){
    for (int i=0; i<d->num_keys;i++){
        if (strcmp(d->keys[i], key)==0){
            return i;
        }
    }
    return -1;
}

void addValue(struct Dictionary *d, const char *key, const int position_idx){
    // if (d->num_keys<=MAX_VAR_NUM){
        int idx=key_idx(d, key);

        //if there exists 'key' in the keys of dictionary
        if (idx!=-1){
            //append position_idx to indices
            d->indices[idx][d->num_idx[idx]]=position_idx;

            //increase the number of indices
            d->num_idx[idx]++;
        }
        
        //if 'key' does not exist in the keys of dictionary
        else {
            //add key
            strcpy(d->keys[d->num_keys], key);

            //append positin_idx to indices
            d->indices[d->num_keys][0]=position_idx;

            //increase the number of indices and the number of keys
            d->num_idx[d->num_keys]++;
            d->num_keys++;
        }
    // }

    // else {
    //     printf("ERROR.(Dictionary is Full)\n");
    // }
   
}

// struct KeyValuePair {
//     char key[MAX_VAR_LEN];
//     double val;
// }

// struct Dictionary {
//     struct KeyValuePair pairs[MAX_VAR_NUM];
    
// }


double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize){
    
    //initialize the result 
    double *result = (double*) malloc(sizeof(double)*queriesSize);
    double initVal = -1.0;
    for (int i=0; i<queriesSize;i++){
        memcpy(&result[i], &initVal, sizeof(double));
    }
    // memset(result, -1.0, sizeof(result));


    //make indice dictionary
    struct Dictionary idx_dict;
    init_dictionary(&idx_dict);

    for (int i=0; i<equationsSize;i++){
        char *a = equations[i][0];
        char *b = equations[i][1];
        addValue(&idx_dict, a, i);
        addValue(&idx_dict, b, i);
    }

    //make set for visited nodes
    struct StringSet ss;
    init_stringset(&ss);

    
    //function for doing dfs search
    double find_result(char *a, char *b, double val){
        // if *a and *b is same
        if (strcmp(a,b)==0){
            return val;
        }

        //append visited nodes
        addString(&ss, a);
        int idx_a = key_idx(&idx_dict, a); //find key
        int j;
        char *c1;
        char *c2;
        double ans;
        //iterate over indices
        for (int i=0; i<idx_dict.num_idx[idx_a];i++){
            j = idx_dict.indices[idx_a][i];
            c1=equations[j][0];
            c2=equations[j][1];
            if ((strcmp(a, c1)==0) && (!contains(&ss, c2))){
                ans=find_result(c2, b, val*values[j]);
                if (ans!=-1.0) {
                    return ans;
                }
            }
            else if ((strcmp(a, c2)==0) && (!contains(&ss, c1))){
                ans=find_result(c1, b, val/values[j]);
                if (ans!=-1.0) {
                    return ans;
                }
            }
            else {continue;}
        }
        return -1;
    }


    //find result for each query
    for (int i=0;i<queriesSize;i++){
        char *a = queries[i][0];
        char *b = queries[i][1];

        // if either *a or *b is not in the list, stay with initial value(-1)
        if ((key_idx(&idx_dict, a)==-1)||(key_idx(&idx_dict, b)==-1)){
            continue;
        }

        // if both *a and *b are in the list, try to find it.
        init_stringset(&ss);
        result[i]=find_result(a, b, 1.0);
    }
    *returnSize = queriesSize;
    return result;
}

int main(void){
    return 0;
}