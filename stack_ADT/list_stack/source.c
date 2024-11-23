#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void push(Node **st, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->next = *st;
    *st = new;
}

int pop(Node **st)
{
    Node *p = *st;
    *st = (*st)->next;
    int n = p->data;
    free(p);
    return n;
}

int top(Node *st)
{
    if (st)
    {
        return st->data;
    }
}

int peak(Node *st, int index)
{
    for (int i = 0; st->next && i < index; i++)
    {
        st = st->next;
    }
    return st->data;
}

int is_empty(Node *st)
{
    return st ? 0 : 1;
}

int main()
{
    return 0;
}