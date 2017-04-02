#include <stdio.h>
#include <stdlib.h>

// Runtime: 132 ms
typedef struct{
    int capacity;
    int top; //index of last value.
    int *data;
}MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize){
    MinStack* stack = malloc(sizeof(MinStack));
    stack->data = malloc(sizeof(int)*maxSize);
    stack->top = -1;
    stack->capacity = maxSize;

    return stack;
}

int IsEmpty(MinStack *obj){
    if(obj->top == -1) 
        return 1;
    return 0;
}

void minStackPush(MinStack* obj, int x){
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
int minStackTop(MinStack* obj) {
    if(obj->top <= -1)
        return -1;
    return obj->data[obj->top];
}

int minStackGetMin(MinStack* obj) {
    if(obj->top == -1)
        return 0;

    int min = *obj->data;

    for(int i = 1; i <= obj->top; i++){
        int value = obj->data[i];
        if(value < min)
            min = value;
    }
    return min;
}

void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj);
}

int main(){

    MinStack *s= minStackCreate(5);

    minStackPop(s);
    minStackPush(s,1);
    minStackPush(s,2);
    minStackPop(s);
    minStackPop(s);
    minStackPop(s);
    minStackPush(s,3);
    minStackPush(s,4);
    minStackPush(s,5);
    minStackPush(s,6);
    minStackPush(s,7);
    minStackPush(s,7);
    minStackPush(s,7);
    minStackPush(s,7);
    minStackPush(s,7);
    minStackPop(s);
    printf("min = %d\n", minStackGetMin(s));

    return 0;
}
