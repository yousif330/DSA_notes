#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack
{
    int size;
    int top;
    char *s;
} Stack;

void create_stack(Stack *st)
{
    st->s = (char *)malloc(sizeof(char) * st->size);
    st->top = -1;
}

void push(Stack *st, char data)
{
    if (st->top < st->size - 1)
    {
        st->s[++st->top] = data;
    }
}

char pop(Stack *st)
{
    if (st->top > -1)
    {
        char r = st->s[st->top--];
        return r;
    }
}

char top(Stack *st)
{
    if (st->top > -1)
    {
        return st->s[st->top];
    }
}

char peak(Stack *st, char index)
{
    index = st->top - index;
    if (index > -1 && index <= st->top)
    {
        return st->s[index];
    }
}

char is_empty(Stack *st)
{
    if (st->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char is_full(Stack *st)
{
    if (st->top == st->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_paren_balance(char s[], int len)
{
    Stack st;
    st.size = len;
    create_stack(&st);

    for (int i = 0; i < len; i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            push(&st, s[i]);
        }
        else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
        {
            if (!is_empty(&st) && (s[i] - 1 == top(&st) || s[i] - 2 == top(&st)))
            {
                pop(&st);
            }
            else
            {
                return 0;
            }
        }
    }

    if (is_empty(&st))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char s[] = "{(12 + 3) + [12-4]}";
    int len = strlen(s);
    printf("%d\n", check_paren_balance(s, len));
    return 0;
}