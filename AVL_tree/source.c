#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int node_height(Node *p)
{
    if (p)
    {
        int hl, hr;
        hl = p->left ? p->left->height : 0;
        hr = p->right ? p->right->height : 0;
        return hl > hr ? hl + 1 : hr + 1;
    }
    return 0;
}

int balance(Node *p)
{
    return node_height(p->left) - node_height(p->right);
}

Node *LL_rotation(Node *p)
{
    Node *pl = p->left;
    Node *plr = pl->right;

    pl->right = p;
    p->left = plr;

    p->height = node_height(p);
    pl->height = node_height(pl);
    return pl;
}

Node *RR_rotation(Node *p)
{
    Node *pr = p->right;
    Node *prl = pr->left;

    pr->left = p;
    p->right = prl;

    p->height = node_height(p);
    pr->height = node_height(pr);
    return pr;
}

Node *LR_rotation(Node *p)
{
    p->left = RR_rotation(p->left);
    return LL_rotation(p);
}

Node *RL_rotation(Node *p)
{
    p->right = LL_rotation(p->right);
    return RR_rotation(p);
}

Node *adjust_height(Node *p)
{
    if (balance(p) == 2 && balance(p->left) >= 0)
    {
        return LL_rotation(p);
    }
    else if (balance(p) == 2 && balance(p->left) == -1)
    {
        return LR_rotation(p);
    }
    else if (balance(p) == -2 && balance(p->right) <= 0)
    {
        return RR_rotation(p);
    }
    else if (balance(p) == -2 && balance(p->right) == 1)
    {
        return RL_rotation(p);
    }

    return p;
}

Node *insert(Node *p, int data)
{
    if (p == NULL)
    {
        Node *new = (Node *)malloc(sizeof(Node));
        new->data = data;
        new->height = 1;
        new->left = new->right = NULL;
        return new;
    }

    if (p->data > data)
    {
        p->left = insert(p->left, data);
    }
    else if (p->data < data)
    {
        p->right = insert(p->right, data);
    }
    p->height = node_height(p);
    p = adjust_height(p);

    return p;
}

Node *in_pre(Node *p)
{
    if (p->left)
    {
        p = p->left;

        while (p->right)
        {
            p = p->right;
        }
    }
    return p;
}

Node *in_succ(Node *p)
{
    if (p->right)
    {
        p = p->right;

        while (p->left)
        {
            p = p->left;
        }
    }
    return p;
}

Node *delete_node(Node *p, int key)
{
    if (p == NULL)
    {
        return p;
    }
    else if (!p->left && !p->right)
    {
        free(p);
        return NULL;
    }

    if (p->data > key)
    {
        p->left = delete_node(p->left, key);
    }
    else if (p->data < key)
    {
        p->right = delete_node(p->right, key);
    }
    else
    {
        if (node_height(p->left) > node_height(p->right))
        {
            Node *q = in_pre(p);
            p->data = q->data;
            p->left = delete_node(p->left, q->data);
        }
        else
        {
            Node *q = in_succ(p);
            p->data = q->data;
            p->right = delete_node(p->right, q->data);
        }
    }
    p->height = node_height(p);
    p = adjust_height(p);

    return p;
}

void display(Node *p)
{
    if (p)
    {
        display(p->left);
        printf("%d ", p->data);
        display(p->right);
    }
}

int main()
{
    Node *root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 25);
    root = insert(root, 15);
    root = insert(root, 40);
    root = insert(root, 10);

    root = delete_node(root, 40);
    root = delete_node(root, 30);
    root = delete_node(root, 15);

    printf("%d\n", balance(root));

    display(root);
    printf("\n");

    return 0;
}