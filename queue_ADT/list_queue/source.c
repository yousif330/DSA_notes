#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
    int length;
} Queue;

void enqueue(Queue *q, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("queue is full\n");
        return;
    }
    new->data = data;

    if (q->front == NULL)
    {
        new->next = q->front;
        q->front = q->rear = new;
        q->length++;
    }
    else
    {
        new->next = q->rear->next;
        q->rear->next = new;
        q->rear = new;
        q->length++;
    }
}

int dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("queue is empty\n");
        return 0;
    }
    else
    {
        Node *p = q->front;
        q->front = q->front->next;
        int r = p->data;
        q->length--;
        free(p);
        return r;
    }
}

void display(Queue *q)
{
    Node *p = q->front;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    Queue q = {0};

    enqueue(&q, 1);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);
    enqueue(&q, 7);
    enqueue(&q, 8);

    printf("length: %d\n", q.length);

    display(&q);

    dequeue(&q);
    dequeue(&q);
    dequeue(&q);
    dequeue(&q);

    printf("length: %d\n", q.length);

    display(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    printf("length: %d\n", q.length);

    display(&q);
    return 0;
}