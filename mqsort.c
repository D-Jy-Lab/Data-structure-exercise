/*
 * @Author: D-Jy
 * @Date: 2021-10-10 23:19:33
 * @LastEditTime: 2021-12-11 15:07:21
 * @LastEditors: Please set LastEditors
 * @Description: 快速排序、二分查找
 * @FilePath: \Code\C\QSort.c
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

/*快速排序*/
int QuickSort(DataType *arr, int low, int high, int mode)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        DataType k = arr[low];
        while (i < j)
        {
            while (i < j && arr[j] >= k) // 从右向左找第一个小于k的数
            {
                j--;
            }
            if (i < j)
            {
                arr[i++] = arr[j];
            }
            while (i < j && arr[i] < k) // 从左向右找第一个大于等于k的数
            {
                i++;
            }
            if (i < j)
            {
                arr[j--] = arr[i];
            }
        }
        arr[i] = k;

        // 输出当前数组
        if (mode)
        {
            printf("第一次快排结果:");
            int num = 0;
            for (num = 0; num < high + 1; num++)
                printf("%d ", (arr[num]));
            printf("\n");
        }

        // 递归调用
        QuickSort(arr, low, i - 1, 0);  // 排序k左边
        QuickSort(arr, i + 1, high, 0); // 排序k右边
    }
    return 0;
}
int QSort(SeqList *list)
{
    if (list->length)
    {
        DataType *arr = list->data;
        QuickSort(arr, 0, list->length - 1, 1);
        return 0;
    }
    else
    {
        printf("快速排序错误，数据为空！\n");
        return -1;
    }
}

/*二分查找*/
int BSearch(SeqList *list, DataType key)
{
    int low, high, mid, count = 0, success = 0;
    low = 0;
    high = list->length - 1;
    while (low <= high) //査找范围不为0时执行循环体语句
    {
        count++;                         // count记录査找次数
        mid = (low + high) / 2;          // 求中间位置
        if (key < list->data[mid])       // key小于中间值时
            high = mid - 1;              // 确定左子表范围
        else if (key > list->data[mid])  // key 大于中间值时
            low = mid + 1;               // 确定右子表范围
        else if (key == list->data[mid]) // 当key等于中间值时，证明查找成功
        {
            printf("查找成功!\n 查找 %d 次!data[%d]=%d", count, mid, key); // 输出査找次数及所査找元素在数组中的位置
            success++;                                                     // success记录查找成功次数
            break;
        }
    }
    if (success == 0) //判断是否查找到内容
        printf("未查找到该数据!\n");
    return 0;
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
    printf("快速排序，二分查找\n");
    SeqList list;
    InitList(&list);
    DataType x;
    int i = 1;
    while (1)
    {
        //输入数据
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
        printf("正在进行快速排序\n");
        printf("排序前:");
        PrintList(&list);
        //将原顺序表倒置
        QSort(&list);
        printf("排序后:");
        PrintList(&list);
        getchar();
        printf("二分查找\n");
        while (1)
        {
            printf("请输入需要查找的数据(0.Exit):");
            scanf("%d", &x);
            if (x == 0)
            {
                break;
            }
            BSearch(&list, x);
        }
    }
    Free(&list);
    getchar();
    return 0;
}
