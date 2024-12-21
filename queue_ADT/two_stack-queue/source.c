#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *s1;
    Node *s2;
} Queue;

void push(Node **head, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;

    new->next = *head;
    *head = new;
}

int pop(Node **head)
{
    if (*head != NULL)
    {
        Node *p = *head;
        *head = (*head)->next;
        int r = p->data;
        free(p);
        return r;
    }
    else
    {
        printf("stack is empty\n");
        return 0;
    }
}

void enqueue(Queue *q, int data)
{
    push(&q->s1, data);
}

int dequeue(Queue *q)
{
    if (q->s1 == NULL && q->s2 == NULL)
    {
        printf("queue is empty\n");
        return 0;
    }
    else if (q->s1 && q->s2 == NULL)
    {
        while (q->s1)
        {
            push(&q->s2, pop(&q->s1));
        }
        return pop(&q->s2);
    }
    else
    {
        return pop(&q->s2);
    }
}

void free_stack(Node **head)
{
    Node *p = NULL;
    while (*head)
    {
        p = *head;
        *head = (*head)->next;
        free(p);
    }
}

int main()
{
    Queue q = {0};
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);

    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    enqueue(&q, 7);
    enqueue(&q, 8);
    enqueue(&q, 9);
    enqueue(&q, 10);

    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));

    free_stack(&q.s1);
    free_stack(&q.s2);
    return 0;
}