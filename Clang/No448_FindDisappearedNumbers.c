#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _SOLUTION_1_ 

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int *hist; 
    int i, miss = 0;
    hist = (int *) malloc((numsSize + 1)* sizeof(int));
    memset(hist,0,sizeof(int) * (numsSize + 1));

    /*
     * nums   [4,3,2,7,8,2,3,1] , then
     * hist [0,1,2,1,1,0,0,1,1] => the numbers of value  
     * index 0 1 2 3 4 5 6 7 8  => map to value, aka nums[i]
     */
    for(i = 0; i < numsSize; i++)
        hist[nums[i]]++;

    for(i = 1; i < numsSize+1; i++){
        if(hist[i] == 0){
            nums[miss] = i;
            miss++;
        }
    }

#ifdef _SOLUTION_1_
    //why I use realloc?? 
    hist = (int*) realloc (hist, miss * sizeof(int));
    for(i = 0; i < miss; i++){
        hist[i] = nums[i];
        printf("%d,", nums[i]);
    }
    *returnSize = miss;
    return hist;
#else
    *returnSize = miss;
    free(hist);
    return nums;
#endif

}

int main(){
    int a[8] = {4,3,2,7,8,2,3,1};
    /*int a[8] = {1,2,2,7,2,2,3,1};*/
    int returnSize = 0;
    int *ans = NULL; 

    ans = findDisappearedNumbers(a, 8, &returnSize);
    for(int i = 0; i<returnSize; i++)
        printf("%d,", ans[i]);
    printf(" is disappeared\n");

#ifdef _SOLUTION_1_
    free(ans);
#endif
    return 0;
}
