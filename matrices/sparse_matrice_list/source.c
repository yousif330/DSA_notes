#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    int col;
    struct Node *next;
} Node;

Node **creat_matrice(int size)
{
    Node **A = (Node **)malloc(sizeof(Node *) * size);
    if (A == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        A[i] == NULL;
    }
    return A;
}

void add_element(Node *A[], int row, int col, int value)
{
    row--;
    col--;
    Node *element = (Node *)malloc(sizeof(Node));
    element->value = value;
    element->col = col;

    if (A[row] == NULL)
    {
        A[row] = element;
        A[row]->next = NULL;
    }
    else
    {
        Node *p = A[row];
        while (p->next && p->next->col < element->col)
        {
            p = p->next;
        }

        element->next = p->next;
        p->next = element;
    }
}

void display(Node *A[])
{
    for (int i = 0; i < 5; i++)
    {
        Node *p = A[i];
        for (int j = 0; j < 6; j++)
        {
            if (p && p->col == j)
            {
                printf("%d ", p->value);
                p = p->next;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

Node **add_matricea(Node *A[], Node *B[])
{
    Node **C = creat_matrice(5);
    for (int i = 0; i < 5; i++)
    {
        Node *a = A[i];
        Node *b = B[i];
        while (a && b)
        {
            if (a->col < b->col)
            {
                add_element(C, i + 1, a->col + 1, a->value);
                a = a->next;
            }
            else if (a->col == b->col)
            {
                add_element(C, i + 1, a->col + 1, a->value + b->value);
                b = b->next;
                a = a->next;
            }
            else
            {
                add_element(C, i + 1, b->col + 1, b->value);
                b = b->next;
            }
        }

        while (b)
        {
            add_element(C, i + 1, b->col + 1, b->value);
            b = b->next;
        }

        while (a)
        {
            add_element(C, i + 1, a->col + 1, a->value);
            a = a->next;
        }
    }
    return C;
}

int main()
{
    Node **A = creat_matrice(5);
    add_element(A, 1, 1, 1);
    add_element(A, 1, 4, 9);
    add_element(A, 2, 2, 3);
    add_element(A, 2, 3, 4);
    display(A);

    printf("\n");

    Node **B = creat_matrice(5);
    add_element(B, 1, 1, 2);
    add_element(B, 1, 5, 7);
    add_element(B, 2, 2, 1);
    add_element(B, 2, 3, 1);
    display(B);

    printf("\n");

    Node **C = add_matricea(A, B);
    display(C);
    return 0;
}