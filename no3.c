#include <stdio.h>
#include <stdlib.h>
#define MAKS 10

typedef struct{
    int parking[MAKS];
    int count;
    int front;
    int rear;
}queue;

typedef struct{
    int parkingTemp[MAKS];
    int count;
}stack;

void inisialisasi(queue *q){
    q->front = q->rear = -1;
    q->count = 0;
}

void inisialisasiStack(stack *s){
    s->count = 0;
}

int full(queue *q){
    return (q->rear == MAKS -1 && q->front == 0) || (q->rear + 1 == q->front);
}

int empty(queue *q){
    return q->front == -1;
}

int fullStack(stack *s){
    return s->count == MAKS;
}

int emptyStack(stack *s){
    return s->count == 0;
}

void pushstack(stack *s, int x){
    if(fullStack(s)){
        printf("Stack penuh");
        return;
    }else{
        s->parkingTemp[s->count] = x;
        s->count++;
    }
}

int popstack(stack *s){
    int temp = -1;
    if(emptyStack(s)){
        printf("Stack kosong");
        return -1;
    }else{
        s->count--;
        temp = s->parkingTemp[s->count];
    }
    return temp;
}

void carOut(int x){
    printf("Car %d has been out\n", x);
}

void enqueue(queue *q, int x){
    if(full(q)){
        printf("Area parkir penuh!");
        return;
    }
    
    if(q->rear == MAKS -1){
        q->rear = 0;
    }else{
        q->rear++;
    }

    q->parking[q->rear] = x;
    q->count++;
    
    if(q->front == -1){
        q->front = 0;
    }
}

void dequeue(queue *q, int x){
    stack s;
    int data, i, j;

    inisialisasiStack(&s);

    if(empty(q)){
        printf("Area parkir kosong");
        return;
    }
        
    j = q->count;
    for(i=0; i<j; i++){
        data = q->parking[q->front];
        q->front = (q->front+1) % MAKS;
        q->count--;

        if(data == x){
            carOut(data);
            break;
        }else{
            pushstack(&s, data);
        }
    }

    int frontTemp = q->front-1;
    for (int i = frontTemp; i < q->rear; i++) {
        q->parking[i] = q->parking[i + 1]; 
    }
    q->rear--;

    int frontTemp2 = q->front-2;
    while(!emptyStack(&s)){
        q->parking[frontTemp2] = popstack(&s);
        frontTemp2--;
        q->count++;
    }

    q->front = 0;
    
    if(q->count == 0){
        q->front = q->rear = -1;
    }
}

void show(queue* q){
    int i, j;

    if(empty(q)){
        printf("Area parkir kosong");
        return;
    }

    printf("Cars in parking lot : ");
    j = q->front;
    for(i=0; i<q->count; i++){
        printf("%d ", q->parking[j]);
        j = (j+1) % MAKS;
    }
}

int main(){
    queue q;
    int choice, num;
    char kar = 'y';

    inisialisasi(&q);
    
    puts("=====Parking Lot Management=====");
    while(kar == 'y' || kar == 'Y'){
        puts("1. In");
        puts("2. Out");
        printf("Enter your choice (1/2): ");
        scanf("%d", &choice);
        printf("Enter your car's number : ");
        scanf("%d", &num);
        fflush(stdin);

        if(choice == 1){
            if(num > 0){
                enqueue(&q, num);
            }else{
                printf("Invalid car number");
                continue;
            }
        }else if(choice == 2){
            if(num > 0){
                dequeue(&q, num);
            }else{
                printf("Invalid car number");
                continue;
            }
        }else{
            printf("Invalid choice\n");
            continue;
        }

        show(&q);

        printf("\nAnything else (y/t) ? ");
        scanf("%c", &kar);
        fflush(stdin);
    }
}