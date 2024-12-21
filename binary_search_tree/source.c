#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void insert(Node **root, int data)
{
    if (*root == NULL)
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = data;
        new->left = new->right = NULL;
        *root = new;
        return;
    }

    Node *p = *root, *t;

    while (p)
    {
        t = p;
        if (p->data == data)
        {
            return;
        }
        else if (p->data > data)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }

    Node *new = (Node *)malloc(sizeof(Node));
    new->data = data;
    new->left = new->right = NULL;

    if (t->data > data)
    {
        t->left = new;
    }
    else
    {
        t->right = new;
    }
}

void generating_BST(Node **root, int a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        insert(&*root, a[i]);
    }
}

Node *search(Node *t, int key)
{
    while (t)
    {
        if (t->data == key)
        {
            return t;
        }
        else if (t->data > key)
        {
            t = t->left;
        }
        else
        {
            t = t->right;
        }
    }
    return t;
}

int height(Node *t)
{
    if (t)
    {
        int left, right;

        left = height(t->left);
        right = height(t->right);

        return left > right ? left + 1 : right + 1;
    }
    return 0;
}

Node *in_pre(Node *t)
{
    if (t->left)
    {
        t = t->left;

        while (t->right)
        {
            t = t->right;
        }
    }
    return t;
}

Node *in_succ(Node *t)
{
    if (t->right)
    {
        t = t->right;

        while (t->left)
        {
            t = t->left;
        }
    }
    return t;
}

Node *delete_node(Node *t, int key)
{
    if (t == NULL)
    {
        return t;
    }
    else if (!t->left && !t->right)
    {
        free(t);
        return NULL;
    }

    if (t->data > key)
    {
        t->left = delete_node(t->left, key);
    }
    else if (t->data < key)
    {
        t->right = delete_node(t->right, key);
    }
    else
    {
        if (height(t->left) > height(t->right))
        {
            Node *q = in_pre(t);
            t->data = q->data;
            t->left = delete_node(t->left, q->data);
        }
        else
        {
            Node *q = in_succ(t);
            t->data = q->data;
            t->right = delete_node(t->right, q->data);
        }
    }
    return t;
}

void display(Node *t)
{
    if (t)
    {
        display(t->left);
        printf("%d ", t->data);
        display(t->right);
    }
}

void free_tree(Node *t)
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
    Node *root = NULL;
    int a[] = {32, 40, 47, 52, 29, 22};
    generating_BST(&root, a, sizeof(a) / sizeof(a[0]));

    display(root);
    printf("\n");

    if (search(root, 32))
    {
        printf("Found\n");
    }
    else
    {
        printf("Not found\n");
    }

    root = delete_node(root, 40);
    display(root);
    printf("\n");

    free_tree(root);

    return 0;
}