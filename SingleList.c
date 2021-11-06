/*
 * @Author: D-Jy
 * @Date: 2021-10-10 18:34:33
 * @LastEditTime: 2021-10-15 16:29:13
 * @LastEditors: Please set LastEditors
 * @Description: 单链表逆置
 * @FilePath: \Code\C\SingleList.c
 */
#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0) //空指针

/*定义单链表*/
typedef struct SingleList
{
    int data;
    struct SingleList *next;
} List;

/*初始化单链表*/
List *InitList(void)
{
    List *head = (List *)malloc(sizeof(List));
    if (!head)
    {
        printf("空间不够，无法建立单链表。\n");
        return NULL;
    }
    head->data = 0;
    head->next = NULL;
    return head;
}

/*判空操作*/
int Empty(List *head)
{
    if (head->next == NULL)
        return 1;
    else
        return 0;
}

/*求顺序表长度*/
int Length(List *head)
{
    return head->data;
}

/*遍历操作*/
void PrintList(List *head)
{
    int i;
    List *ptr = head->next;
    while (ptr)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

/*按值查找*/
int Locate(List *head, int x)
{
    int i = 0;
    List *ptr = head->next;
    while (ptr)
    {
        ++i;
        if (ptr->data == x)
        {
            return i; //返回值所在位置
        }
        ptr = ptr->next;
    }
    return 0;
}

/*按位查找*/
int Get(List *head, int i, int *x)
{ //若查找成功，则通过指针参数x返回值
    if (i < 1 || i > head->data)
    {
        printf("查找位置非法，查找错误\n");
        return -1;
    }
    else
    {
        int count;
        List *ptr = head->next;
        for (count = 1; count < i; count++)
        {
            ptr = ptr->next;
        }
        *x = ptr->data;
        return 0;
    }
}

/*插入操作*/
int Insert(List *head, int i, int x)
{
    if (i < 1 || i > head->data + 1)
    {
        printf("插入位置错误！");
        return -1;
    }
    List *ptr = head;
    int count;
    for (count = 1; count < i; count++)
    {
        ptr = ptr->next;
    }
    List *tmp = (List *)malloc(sizeof(List));
    if (!tmp)
    {
        printf("内存分配失败！");
        return -1;
    }
    tmp->next = ptr->next;
    ptr->next = tmp;
    tmp->data = x;
    head->data++;
    return 0;
}

/*删除操作*/
int Delete(List *head, int i, int *x)
{
    if (i < 1 || i > head->data)
    {
        printf("删除位置错误！");
        return -1;
    }
    List *ptr = head;
    List *tmp;
    int count;
    for (count = 1; count < i; count++)
    {
        ptr = ptr->next;
    }
    if (x)
    {
        *x = ptr->next->data;
    }
    tmp = ptr->next;
    ptr->next = ptr->next->next;
    free(tmp);
    head->data--;
    return 0;
}

/*修改操作*/
int Modify(List *head, int i, int x)
{
    List *ptr = head->next;
    if (i > head->data || i < 1)
    {
        printf("位置错误！\n");
        return -1;
    }
    int count;
    for (count = 1; count < i; count++)
    {
        ptr = ptr->next;
    }
    ptr->data = x;
    return 0;
}

/*单链表逆置*/
int Reverse(List *head)
{
    if (head->next)
    {
        List *pre = NULL;
        List *tmp = NULL;
        while (head->next)
        {
            tmp = head->next->next;
            head->next->next = pre;
            pre = head->next;
            head->next = tmp;
        }
        head->next = pre;
        return 0;
    }
    else
    {
        printf("逆置错误，数据为空！\n");
        return -1;
    }
}

/*内存回收*/
int Free(List *head)
{
    List *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}

int main()
{
    printf("单链表逆置\n");
    List *head = InitList();
    int x;
    int i = 1;
    while (1)
    {
        //输入需要修改的序号
        printf("请输入第%d个数据(0.Exit):", i);
        scanf("%d", &x);
        if (x == 0)
        {
            break;
        }
        if (!Insert(head, i, x))
        {
            i++;
        }
    }
    if (Empty(head))
    {
        printf("数据为空\n");
    }
    else
    {
        printf("逆置前:");
        PrintList(head);
        //将原顺序表倒置
        Reverse(head);
        printf("逆置后:");
        PrintList(head);
        getchar();
    }
    Free(head);
    getchar();
    return 0;
}
