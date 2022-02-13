/*
 * @Author: D-Jy
 * @Date: 2021-10-27 00:59:58
 * @LastEditTime: 2021-11-24 15:24:51
 * @LastEditors: Please set LastEditors
 * @Description: 图的广度优先遍历
 * @FilePath: \Code\C\BFS.c
 */

#include <stdio.h>
#include <stdlib.h>

#define NULL ((void *)0) //空指针
#define MAXSIZE 100      //最大顶点个数

/*指定数据元素的类型*/
typedef int DataType;

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
    tmp->data = (DataType)x;
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
DataType Pop(Queue *queue)
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
    DataType x = ptr->data;
    queue->head = ptr->next;
    free(ptr);
    if (queue->length == 1)
    {
        queue->rear = NULL;
    }
    queue->length--;
    return x;
}

/*获取队首元素*/
DataType GetQueueFront(Queue *queue)
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
    return ptr->data;
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
    char flag = 2;
    DataType chart[MAXSIZE][MAXSIZE] = {0}, a = 0, b = 0, max = 0;
    printf("输入无向图边(X-X):\n");
    while (flag == 2)
    {
        flag = scanf("%d-%d", &a, &b);
        if (a != b && flag == 2)
        {
            chart[a - 1][b - 1] = 1;
            chart[b - 1][a - 1] = 1;
            if (a > max)
            {
                max = a;
            }
            if (b > max)
            {
                max = b;
            }
        }
    }
    if (!max)
    {
        printf("未输入有效数据");
        return -1;
    }
    Queue *q = InitQueue();
    printf("请输入广度优先遍历起点:");
    scanf("%d", &a);
    Push(q, a);
    while (Length(q))
    {
        int i, j;
        for (i = 0; i < max; i++)
        {
            if (chart[GetQueueFront(q) - 1][i] == 1)
            {
                Push(q, i + 1);
                chart[i][GetQueueFront(q) - 1] = 0;
                for (j = 0; j < max; j++)
                {
                    chart[j][i] = 0;
                }
            }
        }
        printf("%d ", Pop(q));
    }
    return Free(q);
}

// 1-2 1-3 1-4 1-5 2-4 3-5
