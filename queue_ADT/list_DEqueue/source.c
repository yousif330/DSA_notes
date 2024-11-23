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

void r_enqueue(Queue *q, int data)
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

void f_enqueue(Queue *q, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("queue is full\n");
        return;
    }

    new->next = q->front;

    if (q->front == NULL)
    {
        q->front = q->rear = new;
    }
    else
    {
        q->front = new;
    }
    q->length++;
}

int f_dequeue(Queue *q)
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

int r_dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("queue is empty\n");
        return 0;
    }
    else
    {
        Node *p = q->front;

        while (p->next != q->rear)
        {
            p = p->next;
        }

        int r = p->next->data;
        free(p->next);
        p->next = NULL;
        q->rear = p;
        return r;
    }
}

int main()
{
    return 0;
}