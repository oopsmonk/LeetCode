#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#define _METHOD_ 1
void dump(int *array, int size){
    for(int i = 0; i < size; i++){
        printf("%d,",array[i]);
    }
    printf("\n");
}

void array_reverse(int* nums, int size){
    if(size <= 1)
        return;

    for(int i = 0; i < (size/2); i++){
        int tmp = nums[i];
        nums[i] = nums[size-i-1];
        nums[size-i-1] = tmp;
    }
}

#if _METHOD_ == 0
// rotate to the right by 'k' steps. 
void rotate(int* nums, int numsSize, int k) {
    
    int *tmp = (int *) malloc(numsSize * sizeof(int));
    //array copy
    memcpy(tmp, nums, numsSize*sizeof(int));

    if(k > 0){ // ignore k <= 0
        //steps may out of range.
        k = k%numsSize;
        // array moving
        memcpy(nums, tmp+(numsSize-k), k*sizeof(int));
        memcpy(nums+k, tmp, (numsSize-k)*sizeof(int));
    }
    
}
#elif _METHOD_ == 1
// rotate to the right by 'k' steps.
void rotate(int* nums, int numsSize, int k) {
    dump(nums, numsSize);
    //reverse all elements
    array_reverse(nums, numsSize);
    dump(nums, numsSize);
    //reverse nums[0] ~ nums[k]
    array_reverse(nums, k%numsSize);
    dump(nums, numsSize);
    //reverse nums[k+1] ~ nums[numssize]
    array_reverse(nums+(k%numsSize), numsSize - (k%numsSize));
    dump(nums, numsSize);
}
#endif

int main(){
#if _METHOD_ == 0 // space complexity = O(n), Runtime: 6 ms
    int a[7] = {1,2,3,4,5,6,7}; 
    // k = 3 then [5,6,7,1,2,3,4]
    int k = 5; 
    rotate(a, 7, k);
    dump(a,7);
#elif _METHOD_ == 1 // space complexity = O(1), Runtime: 9 ms
    int a[7] = {1,2,3,4,5,6,7};
    int k = 10;
    rotate(a, 7, k);
#endif
    return 0;
}
