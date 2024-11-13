#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Node
{
    int data;
    struct Node *ptr;
} Node;

int random_number()
{
    srand(time(NULL));
    return (rand() % 100) + 1;
}

void array_to_list(int A[], int n, Node **head)
{
    Node *last, *t;
    *head = (Node *)malloc(sizeof(Node));
    (*head)->data = A[0];
    (*head)->ptr = NULL;
    last = *head;

    for (int i = 1; i < n; i++)
    {
        t = (Node *)malloc(sizeof(Node));
        t->data = A[i];
        t->ptr = NULL;
        last->ptr = t;
        last = t;
    }
}

void display(Node *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->ptr;
    }
    printf("\n");
}

void r_display(Node *head)
{
    if (head)
    {
        printf("%d ", head->data);
        r_display(head->ptr);
    }
    else
        printf("\n");
}

int list_length(Node *head)
{
    int i = 0;
    while (head)
    {
        head = head->ptr;
        i++;
    }
    return i;
}

int sum_of_nodes(Node *head)
{
    int sum = 0;
    while (head)
    {
        sum += head->data;
        head = head->ptr;
    }
    return sum;
}

int max_node(Node *head)
{
    int max = INT_MIN;

    while (head)
    {
        if (max < head->data)
        {
            max = head->data;
        }
        head = head->ptr;
    }
    return max;
}

int search_list(Node **head, int key)
{
    Node *current = *head;

    while (current->ptr)
    {
        if (current->ptr->data == key)
        {
            Node *t = current->ptr;
            current->ptr = t->ptr;
            t->ptr = *head;
            *head = t;
            return 1;
        }
        current = current->ptr;
    }
    return 0;
}

void insert_at(Node **head, int index, int n)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = n;

    if (index <= 0)
    {
        new->ptr = *head;
        *head = new;
    }
    else
    {
        Node *t = *head;
        for (int i = 1; i < index && t->ptr; i++)
        {
            t = t->ptr;
        }
        new->ptr = t->ptr;
        t->ptr = new;
    }
}

void insert_at_head(Node **head, int n)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = n;
    new->ptr = *head;
    *head = new;
}

void insert_at_last(Node **head, int n)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = n;
    new->ptr = NULL;

    static Node *last = NULL;

    if (*head == NULL)
    {
        *head = new;
        last = *head;
        return;
    }
    else if (last == NULL)
    {
        last = *head;
        while (last->ptr)
        {
            last = last->ptr;
        }
    }

    last->ptr = new;
    last = new;
}

void sorted_insert(Node **head, int n)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = n;

    Node *p = *head, *q;

    if (*head == NULL)
    {
        new->ptr = *head;
        *head = new;
    }
    else
    {
        while (p && n > p->data)
        {
            q = p;
            p = p->ptr;
        }
        if (p == *head)
        {
            new->ptr = *head;
            *head = new;
        }
        else
        {
            new->ptr = q->ptr;
            q->ptr = new;
        }
    }
}

void delete_node(Node **head, int index)
{
    if (index >= 1 && index <= list_length(*head) && *head)
    {
        Node *t, *q = *head;

        if (index == 1)
        {
            t = *head;
            *head = (*head)->ptr;
            free(t);
        }
        else
        {
            for (int i = 1; i < index - 1; i++)
            {
                q = q->ptr;
            }
            t = q->ptr;
            q->ptr = q->ptr->ptr;
            free(t);
        }
    }
}

int is_sorted(Node *head)
{
    while (head->ptr)
    {
        if (head->data > head->ptr->data)
        {
            return 0;
        }
        head = head->ptr;
    }
    return 1;
}

void rm_duplicate(Node **head)
{
    Node *p = *head, *q = p->ptr;

    while (q)
    {
        if (q->data != p->data)
        {
            p = q;
            q = q->ptr;
        }
        else
        {
            p->ptr = q->ptr;
            free(q);
            q = p->ptr;
        }
    }
}

void reverse_list(Node **head)
{
    Node *r = NULL;
    Node *q = NULL;
    Node *p = *head;

    while (p)
    {
        r = q;
        q = p;
        p = p->ptr;

        q->ptr = r;
    }
    *head = q;
}

void conc_list(Node **a, Node **b)
{
    Node *t = *a;

    while (t->ptr)
    {
        t = t->ptr;
    }
    t->ptr = *b;
}

Node *merge_list(Node **a, Node **b)
{
    Node *p = NULL;
    Node *r = NULL;

    if ((*a)->data < (*b)->data)
    {
        r = *a;
    }
    else
    {
        r = *b;
    }

    while (*a && *b)
    {
        if ((*a)->data < (*b)->data)
        {
            while (*a && (*a)->data < (*b)->data)
            {
                p = *a;
                *a = (*a)->ptr;
            }
            p->ptr = *b;
        }
        else
        {
            while (*b && (*b)->data < (*a)->data)
            {
                p = *b;
                *b = (*b)->ptr;
            }
            p->ptr = *a;
        }
    }
    *b = NULL;
    *a = NULL;
    return r;
}

int is_loop(Node **head)
{
    Node *p = *head, *q = *head;

    while (p && q)
    {
        p = p->ptr;
        q = q->ptr;
        if (q)
        {
            q = q->ptr;
        }

        if (q == p)
        {
            return 1;
        }
    }
    return 0;
}

void free_list(Node **head)
{
    Node *p;
    while (*head)
    {
        p = *head;
        *head = (*head)->ptr;
        free(p);
    }
}

int main()
{
    Node *list_1 = NULL;
    Node *list_2 = NULL;

    int A[] = {2, 8, 10, 15, 17, 20, 32, 55};
    array_to_list(A, sizeof(A) / sizeof(A[0]), &list_1);
    display(list_1);

    free_list(&list_1);
    return 0;
}