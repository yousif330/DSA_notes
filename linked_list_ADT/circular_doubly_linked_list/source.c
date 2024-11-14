#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

void array_to_list(Node **head, int a[], int n)
{
    Node *last, *t;
    *head = (Node *)malloc(sizeof(Node));
    (*head)->data = a[0];
    (*head)->next = *head;
    (*head)->prev = *head;
    last = *head;

    for (int i = 1; i < n; i++)
    {
        t = (Node *)malloc(sizeof(Node));
        t->data = a[i];
        t->next = last->next;
        t->prev = last;
        last->next = t;
        t->next->prev = t;
        last = t;
    }
}

int dcll_length(Node *head)
{
    Node *p = head;
    int len = 0;

    do
    {
        len++;
        p = p->next;
    } while (p != head);
    return len;
}

void display(Node *head)
{
    Node *p = head;

    do
    {
        printf("%d ", p->data);
        p = p->next;
    } while (p != head);
    printf("\n");
}

void insert_at(Node **head, int index, int data)
{
    if (index >= 0 && index <= dcll_length(*head))
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = data;

        if (index == 0)
        {
            new->next = *head;
            new->prev = (*head)->prev;
            new->prev->next = new;
            (*head)->prev = new;
        }
        else
        {
            Node *p = *head;
            for (int i = 1; i < index; i++)
            {
                p = p->next;
            }
            new->next = p->next;
            new->prev = p;
            p->next = new;
            new->next->prev = new;
        }
    }
}

void delete_at(Node **head, int index)
{
    if (index >= 1 && index <= dcll_length(*head))
    {
        if (index == 1)
        {
            (*head)->prev->next = (*head)->next;
            (*head)->next->prev = (*head)->prev;
            Node *t = *head;
            *head = (*head)->next;
            free(t);
        }
        else
        {
            Node *p = *head;
            for (int i = 1; i < index; i++)
            {
                p = p->next;
            }
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
        }
    }
}

int main()
{
    Node *list1 = NULL;
    int a[] = {2, 4, 6, 8, 10, 12, 14};
    array_to_list(&list1, a, sizeof(a) / sizeof(a[0]));
    display(list1);

    return 0;
}