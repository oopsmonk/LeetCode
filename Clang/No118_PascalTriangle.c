#include <stdio.h>
#include <stdlib.h>

/*#define _recursion_ */

int pascal(int row, int col) {
  if (col == 0 || col == row) {
    return 1;
  } else {
    return pascal(row - 1, col - 1) + pascal(row - 1, col);
  }
}

/**
 * Return an array of arrays.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int** columnSizes) {
    int **ret = (int **)calloc(numRows, sizeof(int *));
    (*columnSizes) = (int *)calloc(numRows, sizeof(int));

    int i, j;
    for (i = 0; i < numRows; i++) {
        (*columnSizes)[i] = i + 1;
        ret[i] = (int *)calloc((*columnSizes)[i], sizeof(int));
#ifdef _recursion_ // Time Limit Exceeded
	for(j=0; j<=i; j++)
	    ret[i][j] = pascal(i,j);
#else // Runtime: 3 ms
        ret[i][0] = 1;
	ret[i][i] = 1;
        for (j = 1; j < i; j++) {
            ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
        }
#endif
    }

    return ret;
}

int main() {

    int rowNums = 6;
    int *columnSizes = NULL;
    int **ret = generate(rowNums, &columnSizes);

    int i, j;
    printf("rowNums = %d\n", rowNums);
    for(i = 0; i < rowNums; i++) {
        /*printf("columnSizes[%d]= %d\n", i, columnSizes[i]);*/
        for (j = 0; j < columnSizes[i]; j++) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }

    for(i = 0; i<rowNums; i++)
        free(ret[i]);
    free(ret);

    return 0;
}
