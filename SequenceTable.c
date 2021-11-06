/*
 * @Author: D-Jy
 * @Date: 2021-10-10 23:19:33
 * @LastEditTime: 2021-10-15 13:12:33
 * @LastEditors: Please set LastEditors
 * @Description: 顺序表逆置
 * @FilePath: \Code\C\SequenceTable.c
 */
#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0) //空指针
#define INITSIZE 20      //顺序表初始长度
#define ADDSIZE 10       //顺序表追加长度

/*指定数据元素的类型*/
typedef int DataType;

/*定义顺序表*/
typedef struct
{
    DataType *data;
    int length;
    int listsize;
} SeqList;

/*初始化顺序表*/
int InitList(SeqList *list)
{
    list->data = (DataType *)malloc(INITSIZE * sizeof(DataType));
    if (!list->data)
    {
        printf("空间不够，无法建立顺序表。\n");
        return -1;
    }
    list->length = 0;
    list->listsize = INITSIZE;
    return 0;
}

/*判空操作*/
int Empty(SeqList *list)
{
    if (list->length == 0)
        return 1;
    else
        return 0;
}

/*求顺序表长度*/
int Length(SeqList *list)
{
    return list->length;
}

/*遍历操作*/
void PrintList(SeqList *list)
{
    int i;
    for (i = 0; i < list->length; i++)
        printf("%d ", (list->data[i]));
    printf("\n");
}

/*按值查找*/
int Locate(SeqList *list, DataType x)
{
    int i;
    for (i = 0; i < list->length; i++)
    {
        if (list->data[i] == x)
        {
            return i + 1; //返回值所在位置
        }
    }
    return 0;
}

/*按位查找*/
int Get(SeqList *list, int i, DataType *ptr)
{ //若查找成功，则通过指针参数ptr返回值
    if (i < 1 || i > list->length)
    {
        printf("查找位置非法，查找错误\n");
        return -1;
    }
    else
    {
        *ptr = list->data[i - 1];
        return 0;
    }
}

/*插入操作*/
int Insert(SeqList *list, int i, DataType x)
{
    if (i < 1 || i > list->length + 1)
    {
        printf("插入位置错误！");
        return -1;
    }
    if (list->length >= list->listsize)
    {
        list->data = (DataType *)realloc(list->data, (list->listsize + ADDSIZE) * sizeof(DataType));
        if (!list->data)
        {
            printf("内存分配失败，上溢错误！");
            return -1;
        }
        list->listsize += ADDSIZE;
    }
    int k;
    for (k = list->length; k > i - 1; k--)
    {
        list->data[k] = list->data[k - 1];
    }
    list->data[i - 1] = x;
    list->length++;
    return 0;
}

/*删除操作*/
int Delete(SeqList *list, int i, int *ptr)
{
    if (list->length == 0)
    {
        printf("发生下溢错误，即将要访问顺序表之前的地址.\n");
        return -1;
    }
    if (i > list->length || i < 1)
    {
        printf("删除位置错误！\n");
        return -1;
    }
    if (ptr)
    {
        *ptr = list->data[i - 1]; //把要删除的数据返回
    }
    int j;
    for (j = i; j < list->length; j++)
    {
        list->data[j - 1] = list->data[j];
    }
    list->length--;
    return 0;
}

/*修改操作*/
int Modify(SeqList *list, int i, int x)
{
    if (i > list->length || i < 1)
    {
        printf("位置错误！\n");
        return -1;
    }
    list->data[i - 1] = x;
    return 0;
}

/*顺序表逆置*/
int Reverse(SeqList *list)
{
    if (list->length)
    {
        int i;
        for (i = 0; i < list->length - 1 - i; i++)
        {
            DataType tmp = list->data[i];
            list->data[i] = list->data[list->length - 1 - i];
            list->data[list->length - 1 - i] = tmp;
        }
        return 0;
    }
    else
    {
        printf("逆置错误，数据为空！\n");
        return -1;
    }
}

/*内存回收*/
int Free(SeqList *list)
{
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->listsize = 0;
    return 0;
}

int main()
{
    printf("顺序表逆置\n");
    SeqList list;
    InitList(&list);
    DataType x;
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
        if (!Insert(&list, i, x))
        {
            i++;
        }
    }
    if (Empty(&list))
    {
        printf("数据为空\n");
    }
    else
    {
        printf("逆置前:");
        PrintList(&list);
        //将原顺序表倒置
        Reverse(&list);
        printf("逆置后:");
        PrintList(&list);
        getchar();
    }
    Free(&list);
    getchar();
    return 0;
}
