#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

/*#define _recursion_*/

int pascal(int row, int col) {
  if (col == 0 || col == row) {
    return 1;
  } else {
    return pascal(row - 1, col - 1) + pascal(row - 1, col);
  }
}

int* getRow(int rowIndex, int* returnSize) {
#ifdef _recursion_  //Time Limit Exceeded
    int *ret = (int *)malloc((rowIndex+1) * sizeof(int));
    int rows = rowIndex;
    *returnSize = rows+1;
    for(int i = 0; i<=rows; i++){
        ret[i] = pascal(rows,i);
    }
    return ret;
#else  // Runtime: 3 ms
    // C(n,k+1) = C(n,k) * (n-k) / (k+1)
    int *ret = (int *)malloc((rowIndex+1) * sizeof(int));
    int n = rowIndex;
    ret[0] = 1;
    for(int k = 0; k < n; k++){
#if 1
        ret[k+1] = (long)ret[k] * (n-k)/(k+1);
#else // int overflow 
        ret[k+1] = ret[k] * (n-k)/(k+1);
#endif
        /*printf("ret[%d]= %d, n=%d, k=%d\n",k+1, ret[k+1],n,k);*/
    }
    *returnSize = n+1;
    return ret;
#endif
}

int main(){
    int index = 30;
    int size = 0;
    int *ret = getRow(index,&size);
    printf("INT_MAX = %d\n", INT_MAX);
    for(int i = 0; i < size; i++)
        printf("%d ",ret[i] );
    free(ret);
}
