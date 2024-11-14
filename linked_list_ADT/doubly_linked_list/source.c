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
    (*head)->prev = NULL;
    (*head)->next = NULL;
    last = *head;

    for (int i = 1; i < n; i++)
    {
        t = (Node *)malloc(sizeof(Node));
        t->data = a[i];
        t->prev = last;
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

void display(Node *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int list_length(Node *p)
{
    int len = 0;

    while (p)
    {
        len++;
        p = p->next;
    }
    return len;
}

void insert_at(Node **head, int index, int data)
{
    if (index >= 0 && index <= list_length(*head))
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = data;

        if (index == 0)
        {
            new->prev = NULL;
            new->next = *head;
            (*head)->prev = new;
            *head = new;
        }
        else
        {
            Node *p = *head;
            for (int i = 1; i < index; i++)
            {
                p = p->next;
            }

            new->next = p->next;
            p->next = new;
            new->prev = p;

            if (new->next)
            {
                new->next->prev = new;
            }
        }
    }
}

void delete_at(Node **head, int index)
{
    if (index >= 1 && index <= list_length(*head))
    {
        if (index == 1)
        {
            *head = (*head)->next;
            if (*head)
            {
                (*head)->prev = NULL;
            }
            free((*head)->prev);
        }
        else
        {
            Node *p = *head;
            for (int i = 1; i < index; i++)
            {
                p = p->next;
            }
            if (p->next == NULL)
            {
                p->prev->next = NULL;
                free(p);
            }
            else
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                free(p);
            }
        }
    }
}

void reverse_list(Node **head)
{
    Node *p = *head;
    while (p)
    {
        Node *t = p->next;
        p->next = p->prev;
        p->prev = t;

        if (p->prev == NULL)
        {
            *head = p;
        }
        p = p->prev;
    }
}

void free_list(Node **head)
{
    while (*head)
    {
        if ((*head)->next == NULL)
        {
            free(*head);
            *head = NULL;
        }
        else
        {
            *head = (*head)->next;
            free((*head)->prev);
        }
    }
}

int main()
{
    Node *list1 = NULL;
    int A[] = {1, 3, 6, 7, 9, 11};
    array_to_list(&list1, A, sizeof(A) / sizeof(A[0]));

    display(list1);
    reverse_list(&list1);
    delete_at(&list1, 6);
    display(list1);

    free_list(&list1);
    return 0;
}