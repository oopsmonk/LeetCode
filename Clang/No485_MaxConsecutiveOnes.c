#include <stdio.h>

int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int ones_counter = 0, max_ones = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] == 1){
            //count ones
            ones_counter+=1;
        }else{
            ones_counter = 0;
        }
        //check max number of ones 
        if(max_ones < ones_counter)
            max_ones = ones_counter;
    }
    return max_ones;
}

int main(){
    /*int array[20] = {1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0};*/
    /*int array[2] = {0,0};*/
    int array[2] = {1,1};
    /*int array[1] = {0};*/
    printf("%d\n", findMaxConsecutiveOnes(array, 2));
    return 0;
}
