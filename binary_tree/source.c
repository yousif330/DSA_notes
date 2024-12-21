#include <stdio.h>
#include <stdlib.h>

typedef struct tNode
{
    int data;
    struct tNode *left;
    struct tNode *right;
} tNode;

typedef struct qNode
{
    tNode *data;
    struct qNode *next;
} qNode;

typedef struct Queue
{
    qNode *front;
    qNode *rear;
    int length;
} Queue;

void enqueue(Queue *q, tNode *data)
{
    qNode *new = (qNode *)malloc(sizeof(qNode));
    if (new == NULL)
    {
        printf("queue is full\n");
        return;
    }
    new->data = data;

    if (q->front == NULL)
    {
        new->next = q->front;
        q->front = q->rear = new;
        q->length++;
    }
    else
    {
        new->next = q->rear->next;
        q->rear->next = new;
        q->rear = new;
        q->length++;
    }
}

tNode *dequeue(Queue *q)
{
    if (q->front == NULL)
    {
        printf("queue is empty\n");
        return 0;
    }
    else
    {
        qNode *p = q->front;
        q->front = q->front->next;
        tNode *r = p->data;
        q->length--;
        free(p);
        return r;
    }
}

tNode *r_dequeque(Queue *q)
{
    if (q->front == NULL)
    {
        return 0;
    }
    else
    {
        qNode *p = q->front;
        while (p->next != NULL && p->next != q->rear)
        {
            p = p->next;
        }

        tNode *r = q->rear->data;
        free(q->rear);
        q->rear = p;
        q->rear->next = NULL;
        q->length--;
        return r;
    }
}

tNode *create_tree()
{
    tNode *root = (tNode *)malloc(sizeof(tNode));
    root->left = root->right = NULL;
    Queue q = {0};
    enqueue(&q, root);

    printf("Enter root element\n");
    scanf(" %d", &root->data);

    int exit = 0;
    int data = 1;

    while (q.length != 0 && data != 0)
    {
        tNode *p = dequeue(&q);

        printf("left child: \n");
        scanf(" %d", &data);

        if (data > 0)
        {
            tNode *t = (tNode *)malloc(sizeof(tNode));
            t->left = t->right = NULL;
            t->data = data;
            enqueue(&q, t);
            p->left = t;
        }

        printf("right child: \n");
        scanf(" %d", &data);

        if (data > 0)
        {
            tNode *t = (tNode *)malloc(sizeof(tNode));
            t->left = t->right = NULL;
            t->data = data;
            enqueue(&q, t);
            p->right = t;
        }

        system("clear");
    }

    return root;
}

void pre_display(tNode *t)
{
    Queue q = {0};

    while (t || q.length != 0)
    {
        if (t)
        {
            printf("%d ", t->data);
            enqueue(&q, t);
            t = t->left;
        }
        else
        {
            t = r_dequeque(&q);
            t = t->right;
        }
    }
    printf("\n");
}

void in_display(tNode *t)
{
    Queue q = {0};

    while (t || q.length != 0)
    {
        if (t)
        {
            enqueue(&q, t);
            t = t->left;
        }
        else
        {
            t = r_dequeque(&q);
            printf("%d ", t->data);
            t = t->right;
        }
    }
    printf("\n");
}

void post_display(tNode *t)
{
    if (t == NULL)
    {
        return;
    }

    post_display(t->left);
    post_display(t->right);
    printf("%d ", t->data);
}

void level_display(tNode *t)
{
    Queue q = {0};
    printf("%d ", t->data);
    enqueue(&q, t);

    while (q.length != 0)
    {
        tNode *p = dequeue(&q);

        if (p->left != NULL)
        {
            printf("%d ", p->left->data);
            enqueue(&q, p->left);
        }

        if (p->right != NULL)
        {
            printf("%d ", p->right->data);
            enqueue(&q, p->right);
        }
    }
    printf("\n");
}

int count_nodes(tNode *t)
{
    Queue q = {0};
    int count = 0;

    while (t || q.length != 0)
    {
        if (t)
        {
            count++;
            enqueue(&q, t);
            t = t->left;
        }
        else
        {
            t = r_dequeque(&q);
            t = t->right;
        }
    }
    return count;
}

int tree_hight(tNode *t)
{
    Queue q = {0};
    int hight = 0;

    while (t || q.length != 0)
    {
        if (q.length > hight)
        {
            hight = q.length;
        }

        if (t)
        {
            enqueue(&q, t);
            t = t->left;
        }
        else
        {
            t = r_dequeque(&q);
            t = t->right;
        }
    }
    return hight - 1;
}

void free_tree(tNode *t)
{
    if (t == NULL)
    {
        return;
    }

    free_tree(t->left);
    free_tree(t->right);

    free(t);
}

int main()
{
    tNode *root = create_tree();

    pre_display(root);

    in_display(root);

    post_display(root);
    printf("\n");

    level_display(root);

    printf("number of nodes is %d\n", count_nodes(root));
    printf("hight of the tree is %d\n", tree_hight(root));

    free_tree(root);

    return 0;
}