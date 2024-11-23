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

Queue q1 = {0}, q2 = {0}, q3 = {0};

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

void p_enqueue(int priority, int data)
{
    switch (priority)
    {
    case 1:
        enqueue(&q1, data);
        break;
    case 2:
        enqueue(&q2, data);
        break;
    case 3:
        enqueue(&q3, data);
        break;
    }
}

int p_dequeue()
{
    if (q1.front != NULL)
    {
        return dequeue(&q1);
    }
    else if (q2.front != NULL)
    {
        return dequeue(&q2);
    }
    else if (q3.front != NULL)
    {
        return dequeue(&q3);
    }
    return 0;
}

int main()
{
    return 0;
}