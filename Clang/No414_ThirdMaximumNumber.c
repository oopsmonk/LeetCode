#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int equal(int *a, int *b){
    if(a == NULL || b == NULL)
        return 0;
    return (*a == *b);
}

int larger(int *a, int *b){
    if(a == NULL)
        return -1;
    if(b == NULL)
        return 1;
    return (*a>*b);
}

int thirdMax(int* nums, int numsSize) {

#if 0 //Runtime: 9 ms
    int *max = NULL, *sec = NULL, *third = NULL;
    if(numsSize == 1)
        return nums[0];
    if(numsSize == 2)
        return (nums[0]<nums[1])?nums[1]:nums[0];

    max = nums;
    for(int i = 1; i < numsSize; i++){
        int *p = nums+i;
        printf("item %d, m %d, s %d, t %d\n", nums[i], max?*max:-940, sec?*sec:-940, third?*third:-940);

        if(equal(max,p) || equal(sec, p) || equal(third, p)) continue;

        if(larger(p,max)){
            third = sec; sec = max; max = p;
        }else if(sec == NULL || larger(p,sec)){
            third = sec; sec = p;
        }else if(third == NULL || larger(p,third)){
            third = p;
        }
    }
    
    if(third == NULL)
        return *max;
    return *third;

#else // Runtime: 3 ms
    int *max = NULL, *sec = NULL, *third = NULL;
    
    if(numsSize == 1)
        return nums[0];
    if(numsSize == 2)
        return (nums[0]<nums[1])?nums[1]:nums[0];

    max = nums;
    for(int i = 1; i < numsSize; i++){
        int *p = nums+i;

        printf("item %d, m %d, s %d, t %d\n", *p, max?*max:-940, sec?*sec:-940, third?*third:-940);
        if(*max < *p){
           if(sec == NULL){
               sec = max;
               max = p;
           }else{
               third = sec;
               sec = max;
               max = p;
           }
        }else if(*max > *p){
            if(sec == NULL){
                sec = p;
            }else{
                if(*sec < *p){
                    third = sec;
                    sec = p;
                }else if(*sec > *p){
                    if(third == NULL){
                        third = p;
                    }else{
                        if(*third < *p)
                            third = p;
                    }
                }
            }
        }
    }

    printf("m %d, s %d, t %d\n", max?*max:-940, sec?*sec:-940, third?*third:-940);
    if(third == NULL)
        return *max;

    return *third;
#endif
}

int main(){

    /*int a[16] = {5,2,4,1,3,6,0,2,2,3,2,4,5,6,7,8};*/
    /*printf("%d\n", thirdMax(a,10));*/
    /*int a[3] = {1,2,-2147483648};*/
    /*printf("%d\n", thirdMax(a,3));*/
    int a[4] = {2,2,3,1};
    printf("%d\n", thirdMax(a,4));
    return 0;
}
