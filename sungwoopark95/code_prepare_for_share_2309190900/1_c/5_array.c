#include <stdio.h>
#define NUM_STU 3

int main(void){
    int mid[NUM_STU];
    int fin[NUM_STU];
    int tot[NUM_STU];

    for (int i=0; i<NUM_STU; i++){
        printf("Input mid score for student (%d) :", i);
        scanf("%d", &mid[i]);
        printf("Input fin score for student (%d) :", i);
        scanf("%d", &fin[i]);
    }

    for (int i=0;i<NUM_STU; i++){
        tot[i]=mid[i]+fin[i];
    }

    for (int i=0; i<NUM_STU;i++){
        printf("Total Score for Student(%d) is %d.\n", i, tot[i]);
    }

    return 0;
}