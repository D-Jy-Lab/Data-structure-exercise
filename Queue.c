/*
 * @Author: D-Jy
 * @Date: 2021-10-27 00:59:58
 * @LastEditTime: 2021-10-27 03:53:43
 * @LastEditors: Please set LastEditors
 * @Description: 火车调度-队列
 * @FilePath: \Code\C\Stack.c
 */
#include <stdio.h>
#include <stdlib.h>

#define NULL ((void *)0) //空指针

/*指定数据元素的类型*/
typedef char DataType;

/*定义队列*/
typedef struct
{
    struct QueueElement *head;
    struct QueueElement *rear;
    int length;
} Queue;

typedef struct QueueElement
{
    DataType data;
    struct QueueElement *next;
} QueueData;

/*初始化队列*/
Queue *InitQueue(void)
{
    Queue *new = (Queue *)malloc(sizeof(Queue));
    if (!new)
    {
        printf("空间不足，无法创建队列。\n");
        return NULL;
    }
    new->head = NULL;
    new->rear = NULL;
    new->length = 0;
    return new;
}

/*求队列长度*/
int Length(Queue *queue)
{
    if (!queue)
    {
        printf("未初始化队列。\n");
        return 0;
    }
    return queue->length;
}

/*入队操作*/
int Push(Queue *queue, DataType x)
{
    if (!queue)
    {
        printf("未初始化队列。\n");
        return -1;
    }
    QueueData *tmp = (QueueData *)malloc(sizeof(QueueData));
    if (!tmp)
    {
        printf("内存分配失败！");
        return -1;
    }
    tmp->data = x;
    tmp->next = NULL;
    if (queue->length == 0)
    {
        queue->rear = tmp;
        queue->head = tmp;
    }
    else
    {
        queue->rear->next = tmp;
        queue->rear = tmp;
    }
    queue->length++;
    return 0;
}

/*出队操作*/
int Pop(Queue *queue, DataType *x)
{
    if (!queue)
    {
        printf("未初始化队列。\n");
        return -1;
    }
    if (!queue->length)
    {
        printf("队列为空！");
        return -1;
    }
    QueueData *ptr = queue->head;
    *x = ptr->data;
    queue->head = ptr->next;
    free(ptr);
    if (queue->length == 1)
    {
        queue->rear = NULL;
    }
    queue->length--;
    return 0;
}

/*内存回收*/
int Free(Queue *queue)
{
    while (queue->head)
    {
        queue->rear = queue->head->next;
        free(queue->head);
        queue->head = queue->rear;
    }
    free(queue);
    return 0;
}

int main()
{
    Queue *qs = InitQueue();
    Queue *qh = InitQueue();
    DataType c;
    printf("软席为 S ，硬席为 H\n请输入车厢序列:");
    do
    {
        c = getchar();
        if (c == 'S')
        {
            Push(qs, c);
        }
        if (c == 'H')
        {
            Push(qh, c);
        }
    } while (c == 'S' || c == 'H');
    printf("排序后:");
    while (Length(qs))
    {
        Pop(qs, &c);
        putchar(c);
    }
    while (Length(qh))
    {
        Pop(qh, &c);
        putchar(c);
    }
    return 0;
}
