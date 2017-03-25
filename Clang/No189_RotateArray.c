#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

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

int main(){
    int a[7] = {1,2,3,4,5,6,7}; 
    // k = 3 then [5,6,7,1,2,3,4]
    int k = 5; 
    int n = 7;
    rotate(a, n, k);
    for(int i = 0; i < n; i++){
        printf("%d,",a[i]);
    }
    printf("\n");

    return 0;
}
