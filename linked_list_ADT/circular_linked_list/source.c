#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void array_to_cl(Node **head, int a[], int n)
{
    Node *last, *t;
    *head = (Node *)malloc(sizeof(Node));
    (*head)->data = a[0];
    (*head)->next = *head;
    last = *head;

    for (int i = 1; i < n; i++)
    {
        t = (Node *)malloc(sizeof(Node));
        t->data = a[i];
        t->next = *head;
        last->next = t;
        last = t;
    }
}

int cl_length(Node *head)
{
    int count = 0;
    Node *p = head;
    do
    {
        p = p->next;
        count++;
    } while (p != head);
    return count;
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

void r_display(Node *head, Node *p)
{
    static int flag = 0;
    if (p != head || flag == 0)
    {
        flag = 1;
        printf("%d ", p->data);
        r_display(head, p->next);
    }
    else
    {
        printf("\n");
    }
}

void inset_at(Node **head, int index, int data)
{
    if (index >= 0 && index <= cl_length(*head))
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = data;

        Node *p = *head;
        if (index == 0)
        {
            if (*head == NULL)
            {
                *head = new;
                (*head)->next = *head;
            }
            while (p->next != *head)
            {
                p = p->next;
            }
            p->next = new;
            new->next = *head;
        }
        else
        {
            for (int i = 1; i < index; i++)
            {
                p = p->next;
            }
            new->next = p->next;
            p->next = new;
        }
    }
}

void delete_node(Node **head, int index)
{
    if (index >= 1 && index <= cl_length(*head) && *head)
    {
        Node *p = *head;
        if (index == 1)
        {
            while (p->next != *head)
            {
                p = p->next;
            }
            if (p == *head)
            {
                free(*head);
                *head = NULL;
            }
            Node *t = p->next;
            p->next = t->next;
            free(t);
            *head = p->next;
        }
        else
        {
            for (int i = 1; i < index - 1; i++)
            {
                p = p->next;
            }
            Node *t = p->next;
            p->next = t->next;
            free(t);
        }
    }
}

void free_cl(Node *head)
{
    Node *p = head, *q;
    do
    {
        q = p;
        p = p->next;
        free(q);
    } while (p != head);
    p->next = NULL;
}

int main()
{
    Node *list1;
    int a[] = {2, 4, 6, 7, 9, 12, 13, 15};
    array_to_cl(&list1, a, 8);
    display(list1);

    delete_node(&list1, 3);
    display(list1);

    free_cl(list1);
    return 0;
}