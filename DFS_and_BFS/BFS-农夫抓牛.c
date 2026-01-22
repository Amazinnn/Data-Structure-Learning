/*题目描述
FJ 丢了一头牛，决定将其找回。
FJ 和牛位于数轴上，初始位置分别为 x 和 y，牛保持不动。
每次移动时，若 FJ 处于位置 p，他可移动至 p+1、p-1 或 2×p。
计算 FJ 抓住牛所需的最少移动次数。

输入格式
第一行为一个整数 t (1≤t≤10)，表示数据组数；
接下来每行包含一个两个正整数 x,y (0<x,y≤10^5)，分别表示 FJ 和牛的坐标。

输出格式
对于每组数据，输出最少步数，每组数据间用换行隔开。
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 100001

typedef struct {
	int pos;
	int step;
} Node;

typedef struct {
	Node data[MAX];
	int front;
	int rear;
} Queue;

void Init(Queue *queue)
{
	queue->front=queue->rear=0;
}

void EnQueue(Queue *queue,int pos,int step)
{
	queue->data[queue->rear].pos=pos;
	queue->data[queue->rear].step=step;
	queue->rear++;
}

Node DeQueue(Queue *queue)
{
	return queue->data[queue->front++];
}

bool isEmpty(Queue *queue)
{
	return queue->front>=queue->rear;
}

bool isExceed(int pos)
{
	return pos<0||pos>MAX;
}

int BFS(int farmer,int cow)
{
	if (farmer==cow) return 0;
	Queue *q=(Queue *)malloc(sizeof(Queue));
	Init(q);
	bool visited[MAX]={false};
	EnQueue(q,farmer,0);
	while (!isEmpty(q)){
		Node curr=DeQueue(q);
		int pos=curr.pos;
		int NextPos[3]={pos-1,pos+1,pos*2};
		for (int i=0;i<3;i++){
			if (!isExceed(NextPos[i])&&!visited[NextPos[i]]){
				if (NextPos[i]==cow){
					return curr.step+1;
				}
				else {
					EnQueue(q,NextPos[i],curr.step+1);
					visited[NextPos[i]]=true;
				}
			}
		}
	}
	return -1;
}

int main(void)
{
	int n;
	scanf("%d",&n);
	while (n--){
		int farmer,cow;
		scanf("%d %d",&farmer,&cow);
		printf("%d\n",BFS(farmer,cow));
	}
	return 0;
}











