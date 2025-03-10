#include<stdio.h>
#include<string.h>
#define MAX 30

typedef struct {
    char nrp[20];
    char nama[50];
    int nilai;
} Mahasiswa;

typedef struct {
    Mahasiswa mhs[MAX];
    int front;
    int rear;
    int count;
} Queue;

void Inisialisasi(Queue *q){
    q->front = q->rear = q->count = 0;
}

int Kosong(Queue *q){
    return (q->count==0);
}

int Penuh(Queue *q){
    return (q->count==MAX);
}

void Enqueue(Queue *q, Mahasiswa x){
    if(Penuh(q)){
        printf("Queue penuh\n");
    }else{
        strcpy(q->mhs[q->rear].nama,x.nama);
        strcpy(q->mhs[q->rear].nrp,x.nrp);
        q->mhs[q->rear].nilai = x.nilai;

        q->rear = (q->rear+1) % MAX;
        q->count++;
    }

}

Mahasiswa Dequeue(Queue *q){
    Mahasiswa temp;

    strcpy(temp.nrp," ");
    strcpy(temp.nama," ");
    temp.nilai = 0;

    if(Kosong(q)){
        printf("Queue kosong\n");
    }else{
        strcpy(temp.nrp,q->mhs[q->front].nrp);
        strcpy(temp.nama,q->mhs[q->front].nama);
        temp.nilai = q->mhs[q->front].nilai;
        q->front = (q->front+1) % MAX;
        q->count--;
    }

    return temp;
}

void Enqueue_Priority(Queue *q){
    Mahasiswa temp[MAX], swap;
    int i, j;

    for(i=0;i<q->count;i++){
        temp[i] = q->mhs[(q->front+i % MAX)];
    }

    for(i=0; i<q->count-1; i++){
        for (j=0; j<q->count-i-1; j++){
            if (temp[j].nilai < temp[j + 1].nilai){
                swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    int total = q->count;
    Inisialisasi(q);

    for (i = 0; i < total; i++) {
        Enqueue(q, temp[i]);
    }
}


void show(Queue *q){
    if (Kosong(q)) {
        printf("Queue kosong!\n");
        return;
    }

    int i, j;
    for (i = 0, j = q->front; i < q->count; i++, j = (j + 1) % MAX) {
        printf("%s %s %d\n", q->mhs[j].nama, q->mhs[j].nrp, q->mhs[j].nilai);
    }
}

int main(){
    Queue ant;
    Mahasiswa x;
    char kar = 'y';

    Inisialisasi(&ant);

    printf("=====Daftar Mahasiswa=====\n");
    while(kar == 'y'){
        printf("Nama : ");
        fgets(x.nama, 50, stdin);
        x.nama[strcspn(x.nama, "\n")] = '\0';
        
        printf("NRP : ");
        fgets(x.nrp, 50, stdin);
        x.nrp[strcspn(x.nrp, "\n")] = '\0';
    
        printf("Nilai : ");
        scanf("%d", &x.nilai);
    
        Enqueue(&ant,x);

        printf("Ada data lagi (y/t) ? ");
        scanf(" %c", &kar);
        fflush(stdin);
    }

    printf("\nData sebelum diurutkan:\n");
    show(&ant);

    Enqueue_Priority(&ant);

    printf("\nData setelah diurutkan:\n");
    show(&ant);

    return 0;
}