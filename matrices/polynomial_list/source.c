#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    int pow;
    int coeff;
    struct Node *next;
} Node;

void create_exp(Node **head, int row, int A[row][2])
{
    Node *t, *last;
    *head = (Node *)malloc(sizeof(Node));
    (*head)->coeff = A[0][0];
    (*head)->pow = A[0][1];
    (*head)->next = NULL;
    last = (*head);

    for (int i = 1; i < row; i++)
    {
        t = (Node *)malloc(sizeof(Node));
        t->coeff = A[i][0];
        t->pow = A[i][1];
        t->next = last->next;
        last->next = t;
        last = t;
    }
}

int evaluate_exp(Node **head, int x)
{
    Node *p = *head;
    int sum = 0;

    while (p)
    {
        int n = pow(x, p->pow) * p->coeff;
        sum += n;
        p = p->next;
    }

    return sum;
}

void add_node(Node **head, int pow, int coeff)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->pow = pow;
    new->coeff = coeff;

    if (*head == NULL)
    {
        new->next = *head;
        *head = new;
    }
    else
    {
        Node *p = *head;
        while (p->next)
        {
            p = p->next;
        }
        new->next = p->next;
        p->next = new;
    }
}

Node *add_exp(Node *a, Node *b)
{
    Node *exp = NULL;
    while (a && b)
    {
        if (a->pow > b->pow)
        {
            add_node(&exp, a->pow, a->coeff);
            a = a->next;
        }
        else if (a->pow < b->pow)
        {
            add_node(&exp, b->pow, b->coeff);
            b = b->next;
        }
        else
        {
            add_node(&exp, a->pow, b->coeff + a->coeff);
            a = a->next;
            b = b->next;
        }
    }

    while (a)
    {
        add_node(&exp, a->pow, a->coeff);
        a = a->next;
    }

    while (b)
    {
        add_node(&exp, b->pow, b->coeff);
        b = b->next;
    }

    return exp;
}

void display(Node *p)
{
    while (p)
    {
        if (p->pow > 1)
        {
            printf("%dx^%d", p->coeff, p->pow);
        }
        else if (p->pow == 1)
        {
            printf("%dx", p->coeff);
        }
        else
        {
            printf("%d", p->coeff);
        }

        if (p->next)
        {
            printf(" + ");
        }
        else
        {
            printf("\n");
        }
        p = p->next;
    }
}

int main()
{
    Node *exp1 = NULL;
    int a[][2] = {{2, 2}, {3, 1}, {5, 0}};
    create_exp(&exp1, 3, a);

    display(exp1);

    Node *exp2 = NULL;
    int b[][2] = {{3, 3}, {4, 2}, {5, 1}};
    create_exp(&exp2, 3, b);

    display(exp2);

    Node *exp3 = add_exp(exp1, exp2);

    display(exp3);

    return 0;
}