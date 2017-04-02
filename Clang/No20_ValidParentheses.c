#include <stdio.h>
#include <stdlib.h>

//Runtime: 3 ms
typedef int bool;

typedef struct{
    int capacity;
    int top; //index of last value.
    char *data;
}MinStack;

MinStack* minStackCreate(int maxSize){
    MinStack* stack = malloc(sizeof(MinStack));
    stack->data = malloc(sizeof(char)*maxSize);
    stack->top = -1;
    stack->capacity = maxSize;

    return stack;
}

int IsEmpty(MinStack *obj){
    if(obj->top == -1) 
        return 1;
    return 0;
}

void minStackPush(MinStack* obj, char x){
    if(obj->top != obj->capacity){
        obj->top++;
        obj->data[obj->top] = x;
        printf("push: value = %d, top = %d, cap = %d\n", x, obj->top, obj->capacity);
    }
}

void minStackPop(MinStack* obj){
    if(!IsEmpty(obj)){
        obj->top--;
        printf("pop: value = %d, top = %d, cap = %d\n", obj->data[obj->top], obj->top, obj->capacity);
    }
}
char getTop(MinStack* obj) {
    return obj->data[obj->top];
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj);
}

bool isValid(char* s) {
    MinStack *sk= minStackCreate(10000); //string may more than 7000 characters.
    char *p = s;
    int ret = -1;

    while(*p != '\0'){
        printf("%c,",*p);
        if(IsEmpty(sk))
            minStackPush(sk, *p);
        else{
            char tmp = getTop(sk);
            if((tmp == '[' && *p == ']') || 
               (tmp == '{' && *p == '}') || 
               (tmp == '(' && *p == ')')){
                minStackPop(sk);
            }else{
                minStackPush(sk, *p);
            }
        }
        p++;
    }

    ret = IsEmpty(sk);
    minStackFree(sk);
    return ret;
}

int main(){
    char *a = "[[(())]]]";
    printf("valid %d\n", isValid(a));

    return 0;
}

