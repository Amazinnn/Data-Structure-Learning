/*
# P2196 [NOIP 1996 提高组] 挖地雷

## 题目描述
在一个地图上有 $N\ (N \le 20)$ 个地窖，每个地窖中埋有一定数量的地雷。
同时，给出地窖之间的连接路径。当地窖及其连接的数据给出之后，
某人可以从任一处开始挖地雷，然后每次可以移动到一个编号比当前节点大且联通的节点去挖地雷，
当无满足条件的节点时挖地雷工作结束。设计一个挖地雷的方案，使某人能挖到最多的地雷。

## 输入格式
有若干行。
第 $1$ 行只有一个数字，表示地窖的个数 $N$。
第 $2$ 行有 $N$ 个数，分别表示每个地窖中的地雷个数。
第 $3$ 行至第 $N+1$ 行表示地窖之间的连接情况：
第 $3$ 行有 $n-1$ 个数（$0$ 或 $1$），
表示第一个地窖至第 $2$ 个、第 $3$ 个 $\dots$ 第 $n$ 个地窖有否路径连接。
如第 $3$ 行为 $1\space 1\space 0\space 0\space 0\cdots 0$，
则表示第 $1$ 个地窖至第 $2$ 个地窖有路径，
至第 $3$ 个地窖有路径，至第 $4$ 个地窖、第 $5$ 个 $\dots$ 第 $n$ 个地窖没有路径。
第 $4$ 行有 $n-2$ 个数，表示第二个地窖至第 $3$ 个、第 $4$ 个 $\dots$ 第 $n$ 个地窖有否路径连接。
…… 
第 $n+1$ 行有 $1$ 个数，表示第 $n-1$ 个地窖至第 $n$ 个地窖有否路径连接。（为 $0$ 表示没有路径，为 $1$ 表示有路径）。

## 输出格式
第一行表示挖得最多地雷时的挖地雷的顺序，各地窖序号间以一个空格分隔，不得有多余的空格。
第二行只有一个数，表示能挖到的最多地雷数。


NOIP 1996 提高组第三题。
*/
#include <stdio.h>
#include <stdlib.h> 
#define MAX 21  // 定义最大地窖数常量

/* 链表节点结构体：用于存储路径信息
 * num: 地窖编号
 * next: 指向下一个节点的指针
 */
typedef struct node{
    int num;
    struct node *next;
} node;

// 全局变量定义
int total[MAX] = {0};      // total[i]: 以地窖i为终点的最大地雷数
int ansTotal = 0;          // 全局最大地雷数
int ansEnd = 0;            // 达到最大地雷数的终点地窖编号
node *list[MAX] = {NULL};  // 邻接表：list[i]存储所有能到达地窖i的前驱地窖（反向建边）
node *record[MAX] = {NULL}; // 路径记录：record[i]存储到达地窖i的最优路径（头插法，路径逆序存储）

/* 函数功能：向邻接表中添加边（反向建边）
 * 参数：a-邻接表数组，from-起点地窖，to-终点地窖
 * 说明：采用头插法，将from添加到to的邻接表中
 */
void enlist(node **a, int from, int to)
{
    node *newnode = (node *)malloc(sizeof(node));  // 创建新节点
    newnode->num = from;          // 设置节点值为起点地窖编号
    newnode->next = NULL;         // 初始化next指针
    
    // 头插法：新节点插入链表头部
    if (a[to] != NULL) 
        newnode->next = a[to];     // 新节点指向原头节点
    a[to] = newnode;              // 更新头指针指向新节点
}

/* 函数功能：递归打印路径（从起点到终点）
 * 参数：curr-当前链表节点
 * 说明：利用递归栈实现逆序打印（链表存储是逆序的）
 */
void Print(node *curr)
{
    if (curr->next != NULL) 
        Print(curr->next);  // 先递归打印后续节点
    
    // 打印当前节点（根据位置决定是否加空格）
    if (curr->next != NULL) 
        printf(" %d", curr->num);
    else 
        printf("%d", curr->num);  // 最后一个节点不加空格
}

int main(void)
{
    int N;  // 地窖总数
    scanf("%d", &N);
    
    int landmine[N+1];  // 存储每个地窖的地雷数（索引从1开始）
    for (int i = 1; i <= N; i++) 
        scanf("%d", &landmine[i]);  // 读取每个地窖的地雷数
    
    // 构建邻接矩阵：读取地窖连接关系
    for (int i = 1; i < N; i++) {
        for (int j = i+1; j <= N; j++) {
            int link;
            scanf("%d", &link);  // 读取连接标志（0无连接，1有连接）
            if (link == 1) 
                enlist(list, i, j);  // 反向建边：i->j 表示从i可到达j
        }
    }
    
    // 动态规划主循环：计算每个地窖作为终点时的最大地雷数
    for (int end = 1; end <= N; end++) {
        if (list[end] == NULL) {
            // 情况1：当前地窖没有前驱（可能是起点）
            enlist(record, end, end);  // 路径就是自身
            total[end] = landmine[end];  // 地雷数就是自身地雷数
        }
        else {
            // 情况2：当前地窖有前驱，寻找最优前驱
            int front = 1;      // 记录最优前驱地窖
            int max = 0;        // 记录前驱中的最大地雷数
            node *curr = list[end];  // 遍历所有前驱地窖
            
            // 遍历所有前驱，找到地雷数最多的路径
            while (curr != NULL) {
                if (max < total[curr->num]) {
                    front = curr->num;     // 更新最优前驱
                    max = total[front];   // 更新最大地雷数
                }
                curr = curr->next;
            }
            
            // 更新路径：继承最优前驱的路径，并添加当前地窖
            record[end] = record[front];  // 复制前驱路径（浅拷贝-共享路径）
            enlist(record, end, end);     // 头插法添加当前地窖到路径中
            total[end] = total[front] + landmine[end];  // 更新总地雷数
        }
        
        // 更新全局最优解
        if (ansTotal < total[end]) {
            ansEnd = end;       // 更新最优终点
            ansTotal = total[end];  // 更新最大地雷数
        }
    }
    
    // 输出结果
    Print(record[ansEnd]);  // 打印最优路径（从起点到终点）
    printf("\n");
    printf("%d", ansTotal);  // 输出最大地雷数
    
    return 0;
}













