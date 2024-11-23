#include <stdio.h>
#include <stdlib.h>

typedef struct Queue
{
    int *array;
    int size;
    int rear;
    int front;
} Queue;

void create_queue(Queue *q)
{
    q->front = q->rear = 0;
    q->array = (int *)malloc(sizeof(int) * q->size);
    if (q->array == NULL)
    {
        return;
    }
}

void enqueue(Queue *q, int data)
{
    if ((q->rear + 1) % q->size != q->front)
    {
        q->rear = (q->rear + 1) % q->size;
        q->array[q->rear] = data;
    }
}

int dequeue(Queue *q)
{
    if (q->front != q->rear)
    {
        q->front = (q->front + 1) % q->size;
        return q->array[q->front];
    }
    return 0;
}

int is_empty(Queue *q)
{
    if (q->front == q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_full(Queue *q)
{
    if ((q->rear + 1) % q->size == q->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void display(Queue *q)
{
    int p = q->front;
    do
    {
        p = (p + 1) % q->size;
        printf("%d ", q->array[p]);
    } while (p != q->rear);
    printf("\n");
}

int main()
{
    Queue q;
    q.size = 7;
    create_queue(&q);
    enqueue(&q, 1);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);
    enqueue(&q, 7);
    enqueue(&q, 8);

    display(&q);

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);

    display(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    display(&q);

    free(q.array);
    return 0;
}