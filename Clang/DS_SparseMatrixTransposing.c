/*
 * Fundamentals of Data Structures in C++ 
 * Charpter 2 Array
 */

#include <stdio.h> 
#include <stdlib.h> //malloc, rand
#include <time.h> // time_t

#define MaxTerms 200 
#define R_C 0 // 1: stored in row*col order, 0:stored in col*row order. 
/*#define _STATIC_ARRAY_ */

typedef struct MatrixTerm{
    int row;
    int col;
    int value;
} MatrixTerm;

typedef struct SparseMatrix{
    int Rows;
    int Cols;
    int Terms;
    MatrixTerm smArray[MaxTerms];
} SparseMatrix;

//dynamic matrix 
typedef struct DMatrixTerm{
    long row;
    long col;
    int value;
} DMatrixTerm;

typedef struct DSparseMatrix{
    long Rows;
    long Cols;
    long long Terms;
    DMatrixTerm *smArray;
} DSparseMatrix;

void simpleMatrix(SparseMatrix *m ){
/* Sparse Matrix 

15,  0,   0,   22,  0,  -15
0,   11,  3,   0,   0,  0
0,   0,   0,   -6,  0,  0
0,   0,   0,   0,   0,  0
91,  0,   0,   0,   0,  0
0,   0,   28,  0,   0,  0

*/

#if R_C
    MatrixTerm t;
    m->Rows = 6, m->Cols = 6, m->Terms = 0;
    t.row = 0, t.col = 0, t.value = 15;
    m->smArray[0] = t, m->Terms +=1;
    t.row = 0, t.col = 3, t.value = 22;
    m->smArray[1] = t, m->Terms +=1;
    t.row = 0, t.col = 5, t.value = -15;
    m->smArray[2] = t, m->Terms +=1;
    t.row = 1, t.col = 1, t.value = 11;
    m->smArray[3] = t, m->Terms +=1;
    t.row = 1, t.col = 2, t.value = 3;
    m->smArray[4] = t, m->Terms +=1;
    t.row = 2, t.col = 3, t.value = -6;
    m->smArray[5] = t, m->Terms +=1;
    t.row = 4, t.col = 0, t.value = 91;
    m->smArray[6] = t, m->Terms +=1;
    t.row = 5, t.col = 2, t.value = 28;
    m->smArray[7] = t, m->Terms +=1;
#else
    MatrixTerm t;
    m->Rows = 6, m->Cols = 6, m->Terms = 0;
    t.col = 0, t.row = 0, t.value = 15;
    m->smArray[0] = t, m->Terms +=1;
    t.col = 0, t.row = 4, t.value = 91;
    m->smArray[1] = t, m->Terms +=1;
    t.col = 1, t.row = 1, t.value = 11;
    m->smArray[2] = t, m->Terms +=1;
    t.col = 2, t.row = 1, t.value = 3;
    m->smArray[3] = t, m->Terms +=1;
    t.col = 2, t.row = 5, t.value = 28;
    m->smArray[4] = t, m->Terms +=1;
    t.col = 3, t.row = 0, t.value = 22;
    m->smArray[5] = t, m->Terms +=1;
    t.col = 3, t.row = 2, t.value = -6;
    m->smArray[6] = t, m->Terms +=1;
    t.col = 5, t.row = 0, t.value = -15;
    m->smArray[7] = t, m->Terms +=1;

#endif 
}

void MassMatrix(DSparseMatrix *m){

    m->Rows = 1000, m->Cols = 1000;
    m->Terms = 0;
    m->smArray = (DMatrixTerm *) malloc((m->Rows * m->Cols)* sizeof(DMatrixTerm));
    for(int i = 0; i<m->Cols; i++){
        for(int j = 0; j < m->Rows; j++){
            int value = rand() % 100;
            if(value < 70)
                value = 0;

            if(value != 0){
                m->smArray[m->Terms].row = j;
                m->smArray[m->Terms].col = i;
                m->smArray[m->Terms].value = value;
                m->Terms ++;
            }
        }
    }
}

void dumpMatrix(SparseMatrix *m){

#if R_C
    printf("Stored in Row*Col order:\n");
#else
    printf("Stored in Col*Row order:\n");
#endif

    for(int i=0; i<m->Terms; i++){
        MatrixTerm t = m->smArray[i];
        printf("%d,\t %d,\t %d\n",t.row, t.col, t.value);
    }
}

void dumpDMatrix(DSparseMatrix *m){

    for(int i=0; i<m->Terms; i++){
        DMatrixTerm t = m->smArray[i];
        printf("%ld,\t %ld,\t %d\n",t.row, t.col, t.value);
    }
}

/*
 * Big-O(columns*terms), terms = columns*rows when worst case (non-sparse), 
 * then Big-O(columns*terms) => Big-O(columns*columns*rows) 
 */
SparseMatrix traspose(SparseMatrix *m){
    SparseMatrix b;
    b.Rows = m->Rows;
    b.Cols = m->Cols;
    b.Terms = m->Terms;
    if(m->Terms > 0){
        int CurrentB = 0;
        for(int c = 0; c < m->Cols; c++){       // Big-O(columns)

            for(int i = 0; i< m->Terms; i++){   // Big-O(terms)
                if(m->smArray[i].col == c){
                    b.smArray[CurrentB].row = c;
                    b.smArray[CurrentB].col = m->smArray[i].row;
                    b.smArray[CurrentB].value = m->smArray[i].value;
                    CurrentB ++;
                }
            }
        }
    }

    return b; // Big-O(columns*terms)
}

SparseMatrix FastTraspose(SparseMatrix *m){
    
    int RowSize[m->Cols];
    int RowStart[m->Cols];
    SparseMatrix b;
    b.Rows = m->Cols, b.Cols = m->Rows, b.Terms = m->Terms;
    int i;
    if(m->Terms > 0){

        // initialize 
        for(i = 0; i < m->Cols; i++)    // Big-O(columns)
            RowSize[i] = 0;

        /* Sparse Matrix 
        * 
        *  15,  0,   0,   22,  0,  -15
        *  0,   11,  3,   0,   0,  0
        *  0,   0,   0,   -6,  0,  0
        *  0,   0,   0,   0,   0,  0
        *  91,  0,   0,   0,   0,  0
        *  0,   0,   28,  0,   0,  0
        * 
        *  compute RowSize[i] = number of terms in row i of b 
        *  index     [0],  [1],  [2],  [3],  [4],  [5]
        *  RowSize   3,    2,    1,    0,    1,    1
        *  RowStart  0,    3,    5,    6,    6,    7
        */
        for(i = 0; i < m->Terms; i++)   // Big-O(terms)
            RowSize[m->smArray[i].col]++;

        // initialize start position of row i in b. 
        RowStart[0] = 0;
        for(i = 1; i < m->Cols; i++)    // Big-O(columns-1)
            RowStart[i] = RowStart[i-1] + RowSize[i-1];

        // trasposing 
        for(i = 0; i < m->Terms; i++){  // O(terms)
            int j = RowStart[m->smArray[i].col];
            b.smArray[j].row = m->smArray[i].col;
            b.smArray[j].col = m->smArray[i].row;
            b.smArray[j].value = m->smArray[i].value;
            RowStart[m->smArray[i].col]++;
        }
    }
    return b; // O(terms) => O(row*column) when non-sparse. 
}

//TODO 
int trasposeVerify(){
}

int main(){

#ifdef _STATIC_ARRAY_
    SparseMatrix a;
    simpleMatrix(&a);
    dumpMatrix(&a);
    SparseMatrix b = traspose(&a);
    dumpMatrix(&b);
    b = FastTraspose(&a);
    dumpMatrix(&b);
#else
    time_t t;
    srand((unsigned) time(&t));
    DSparseMatrix d;
    MassMatrix(&d);
    dumpDMatrix(&d);
    
    free(d.smArray);
#endif
    return 0;
}
