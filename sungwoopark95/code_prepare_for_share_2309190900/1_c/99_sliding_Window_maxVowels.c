
typedef struct {
    char data[6];
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

void remove_for_set(Set *set, char value) {
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

int maxVowels(char * s, int k){
    Set set;
    init(&set);
    add(&set, 'a');
    add(&set, 'e');
    add(&set, 'i');
    add(&set, 'o');
    add(&set, 'u');

    int num=0;
    int ans;
    int len=strlen(s);
    for (int i=0; i<k;i++){
        if (contains(&set, s[i])){
            num++;
        }
    }
    ans = num;
    int front=0;
    for (int j=k; j<len; j++){
        if (contains(&set, s[j])){num++;}
        if (contains(&set, s[front])){num--;}
        if (ans<num) {ans=num;}
        front++;
    }
    return ans;
    
}

