/*
 * @Author: D-Jy
 * @Date: 2021-10-27 00:59:58
 * @LastEditTime: 2021-11-15 03:57:19
 * @LastEditors: Please set LastEditors
 * @Description: 二叉树操作
 * @FilePath: \Code\C\BinaryTree.c
 */
#include <stdio.h>
#include <stdlib.h>

#define NULL ((void *)0)

/*指定树数据元素的类型*/
typedef char TreeDataType;

/*定义树*/
typedef struct BinaryTreeNode
{
    TreeDataType data;
    int cont;
    struct BinaryTreeNode *leftChild, *rightChild;
} BinaryTree, *StackDataType;

/*定义栈*/
typedef struct
{
    struct StackElement *data;
    int length;
} Stack;

typedef struct StackElement
{
    StackDataType data;
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
int StackLength(Stack *stack)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return 0;
    }
    return stack->length;
}

/*入栈操作*/
int PushStack(Stack *stack, StackDataType x)
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
StackDataType PopStack(Stack *stack)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return NULL;
    }
    if (!stack->length)
    {
        printf("栈为空！");
        return NULL;
    }
    StackData *ptr = stack->data;
    StackDataType x = ptr->data;
    stack->data = ptr->next;
    free(ptr);
    stack->length--;
    return x;
}

/*获取栈顶元素*/
StackDataType GetStackTop(Stack *stack)
{
    if (!stack)
    {
        printf("未初始化栈。\n");
        return NULL;
    }
    if (!stack->length)
    {
        // printf("栈为空！");
        return NULL;
    }
    StackData *ptr = stack->data;
    return ptr->data;
}

/*内存回收栈*/
int FreeStack(Stack *stack)
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

/*后序遍历内存回收树*/
int FreeTree(BinaryTree *BTree)
{
    if (BTree == NULL)
        return 0;
    if (BTree->leftChild != NULL)
    {
        FreeTree(BTree->leftChild);
        BTree->leftChild = NULL;
    }
    if (BTree->rightChild != NULL)
    {
        FreeTree(BTree->rightChild);
        BTree->rightChild = NULL;
    }
    if (BTree != NULL)
    {
        free(BTree);
        BTree = NULL;
    }
    return 0;
}

/*创建树*/
BinaryTree *CreateBinaryTree()
{
    BinaryTree *BTree = NULL;
    BinaryTree *pBTree = NULL;
    Stack *stack = InitStack();
    printf("请按先序遍历顺序输入二叉树(空输入#):");
    char input = getchar();

    if (!(BTree = malloc(sizeof(BinaryTree))))
    {
        printf("空间不足，无法创建树。\n");
        return NULL;
    }
    BTree->data = input;
    BTree->leftChild = NULL;
    BTree->rightChild = NULL;
    PushStack(stack, BTree);
    int leftStatus = 0;
    while (StackLength(stack))
    {
        if ((input = getchar()) == '#')
        {
            if (leftStatus)
            {
                PopStack(stack)->rightChild = NULL;
            }
            else
            {
                GetStackTop(stack)->leftChild = NULL;
                leftStatus = 1;
            }
        }
        else if (input != '\n')
        {
            if (!(pBTree = malloc(sizeof(BinaryTree))))
            {
                printf("空间不足，无法创建树。\n");
                FreeTree(BTree);
                return NULL;
            }
            pBTree->data = input;
            if (leftStatus)
            {
                PopStack(stack)->rightChild = pBTree;
                leftStatus = 0;
            }
            else
            {
                GetStackTop(stack)->leftChild = pBTree;
            }
            PushStack(stack, pBTree);
        }
        else
        {
            printf("输入错误");
            FreeTree(BTree);
            return NULL;
        }
    }
    FreeStack(stack);
    return BTree;
}

/*先序遍历树*/
void PreorderTraversal(BinaryTree *pBinaryTree)
{
    BinaryTree *pNode = NULL;
    Stack *nodes = InitStack();
    PushStack(nodes, pBinaryTree);
    while (StackLength(nodes))
    {
        pNode = PopStack(nodes);
        if (pNode->rightChild)
        {
            PushStack(nodes, pNode->rightChild);
        }
        if (pNode->leftChild)
        {
            PushStack(nodes, pNode->leftChild);
        }
        putchar(pNode->data);
    }
    putchar('\n');
}

/*中序遍历树*/
void InorderTraversal(BinaryTree *pBinaryTree)
{
    BinaryTree *pNode = pBinaryTree;
    Stack *nodes = InitStack();
    PushStack(nodes, pBinaryTree);
    while (StackLength(nodes))
    {
        while (pNode = GetStackTop(nodes))
        {
            PushStack(nodes, pNode->leftChild);
        }
        PopStack(nodes);
        if (StackLength(nodes))
        {
            pNode = PopStack(nodes);
            putchar(pNode->data);
            PushStack(nodes, pNode->rightChild);
        }
    }
    putchar('\n');
}

/*后序遍历树*/
void PostorderTraversal(BinaryTree *pBinaryTree)
{
    BinaryTree *pNode = pBinaryTree;
    Stack *nodes = InitStack();
    while (pNode || StackLength(nodes))
    {
        while (pNode)
        {
            pNode->cont = 1;
            PushStack(nodes, pNode);
            pNode = pNode->leftChild;
        }
        if (StackLength(nodes))
        {
            pNode = PopStack(nodes);
            if (pNode->cont == 1)
            {
                pNode->cont++;
                PushStack(nodes, pNode);
                pNode = pNode->rightChild;
            }
            else
            {
                if (pNode->cont == 2)
                {
                    putchar(pNode->data);
                    pNode = NULL;
                }
            }
        }
    }
    putchar('\n');
}

int main()
{
    BinaryTree *binaryTree = CreateBinaryTree();
    printf("先序遍历:");
    PreorderTraversal(binaryTree);
    printf("中序遍历:");
    InorderTraversal(binaryTree);
    printf("后序遍历:");
    PostorderTraversal(binaryTree);
    return 0;
}
