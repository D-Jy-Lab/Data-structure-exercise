/*
 * @Author: D-Jy
 * @Date: 2021-10-27 00:59:58
 * @LastEditTime: 2021-10-27 14:57:40
 * @LastEditors: Please set LastEditors
 * @Description: 进制转换-栈
 * @FilePath: \Code\C\Stack.c
 */
#include <stdio.h>
#include <stdlib.h>

#define NULL ((void *)0) //空指针

/*指定数据元素的类型*/
typedef char DataType;

/*定义栈*/
typedef struct
{
    struct StackElement *data;
    int length;
} Stack;

typedef struct StackElement
{
    DataType data;
    struct StackElement *next;
} StackData;

/*初始化栈*/
Stack *InitStack(void)
{
    Stack *new = (Stack *)malloc(sizeof(Stack));
    if (!new)
    {
        printf("空间不足，无法创建栈。\n");
        return NULL;
    }
    new->data = NULL;
    new->length = 0;
    return new;
}

/*求栈长度*/
int Length(Stack *stack)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return 0;
    }
    return stack->length;
}

/*入栈操作*/
int Push(Stack *stack, DataType x)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return -1;
    }
    StackData *tmp = (StackData *)malloc(sizeof(StackData));
    if (!tmp)
    {
        printf("内存分配失败！");
        return -1;
    }
    tmp->next = stack->data;
    stack->data = tmp;
    tmp->data = x;
    stack->length++;
    return 0;
}

/*出栈操作*/
int Pop(Stack *stack, DataType *x)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return -1;
    }
    if (!stack->length)
    {
        printf("栈为空！");
        return -1;
    }
    StackData *ptr = stack->data;
    *x = ptr->data;
    stack->data = ptr->next;
    free(ptr);
    stack->length--;
    return 0;
}

/*内存回收*/
int Free(Stack *stack)
{
    while (stack->data)
    {
        StackData *tmp = stack->data;
        stack->data = tmp->next;
        free(tmp);
    }
    free(stack);
    return 0;
}

/*输出字符*/
void PrintChar(DataType n)
{
    if (n >= 0 && n < 10)
    {
        printf("%d", n);
    }
    else
    {
        printf("%c", 'A' + n - 10);
    }
}

int main()
{
    int x, d = 1;
    printf("请输入一个十进制数:");
    scanf("%d", &x);
    while (d < 2)
    {
        printf("请输入需要转化的进制:");
        scanf("%d", &d);
    }
    Stack *stack = InitStack();
    while (x)
    {
        Push(stack, x % d);
        x = x / d;
    }
    while (Length(stack))
    {
        DataType c;
        Pop(stack, &c);
        PrintChar(c);
    }
    return 0;
}
