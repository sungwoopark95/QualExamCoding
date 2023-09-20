#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_VAR_LEN 6
#define MAX_VAR_NUM 40
#define MAX_EQ_NUM 20

#define MAX_SIZE 20

/*"SET" */
typedef struct {
    char data[MAX_SIZE];
    int size;
} Set;

void init(Set *set) {
    set->size = 0;
}

bool contains(Set *set, char value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) {
            return true;
        }
    }
    return false;
}

void add(Set *set, char value) {
    if (!contains(set, value)) {
        set->data[set->size++] = value;
    }
}

void remove(Set *set, char value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) {
            set->data[i] = set->data[--set->size];
            break;
        }
    }
}

void print(Set *set) {
    printf("{");
    for (int i = 0; i < set->size; i++) {
        printf("'%c'", set->data[i]);
        if (i < set->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
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
