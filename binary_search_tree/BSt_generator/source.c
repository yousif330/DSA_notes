#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct tNode
{
    int data;
    struct tNode *left;
    struct tNode *right;
} tNode;

typedef struct sNode
{
    tNode *data;
    struct sNode *next;
} sNode;

void push(sNode **s, tNode *data)
{
    sNode *new = (sNode *)malloc(sizeof(sNode));
    new->data = data;

    new->next = *s;
    *s = new;
}

tNode *pop(sNode **s)
{
    if (*s == NULL)
    {
        return NULL;
    }
    else
    {
        sNode *t = *s;
        *s = (*s)->next;
        tNode *r = t->data;
        free(t);
        return r;
    }
}

int top(sNode *s)
{
    if (s)
    {
        return s->data->data;
    }
    else
    {
        return INT_MAX;
    }
}

void free_list(sNode *t)
{
    sNode *p = NULL;
    while (t)
    {
        p = t;
        t = t->next;
        free(p);
    }
}

void create_BST(tNode **t, int a[], int len)
{
    *t = (tNode *)malloc(sizeof(tNode));
    (*t)->data = a[0];
    (*t)->left = (*t)->right = NULL;

    tNode *p = *t;
    sNode *s = NULL;
    push(&s, p);
    int i = 0;

    while (i < len)
    {
        if (p->data > a[i])
        {
            tNode *new = (tNode *)malloc(sizeof(tNode));
            new->data = a[i];
            new->left = new->right = NULL;
            p->left = new;
            i++;
            p = new;
            push(&s, p);
        }
        else if ((p->data < a[i] && top(s) > a[i]) || top(s) == (*t)->data)
        {
            tNode *new = (tNode *)malloc(sizeof(tNode));
            new->data = a[i];
            new->left = new->right = NULL;
            p->right = new;
            i++;
            p = new;
        }
        else
        {
            p = pop(&s);
        }
    }
    free_list(s);
}

void display(tNode *t)
{
    if (t)
    {
        display(t->left);
        printf("%d ", t->data);
        display(t->right);
    }
}

void free_tree(tNode *t)
{
    if (t)
    {
        free_tree(t->left);
        free_tree(t->right);
        free(t);
    }
}

int main()
{
    tNode *root = NULL;

    int a[] = {32, 47, 30, 52, 20, 29};
    int len = sizeof(a) / sizeof(a[0]);
    create_BST(&root, a, len);

    display(root);
    printf("\n");

    free_tree(root);
    return 0;
}