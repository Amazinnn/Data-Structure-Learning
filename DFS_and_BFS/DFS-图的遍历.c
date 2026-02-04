/*
# P3916 图的遍历

## 题目描述
给出 $N$ 个点，$M$ 条边的有向图，对于每个点 $v$，
令 $A(v)$ 表示从点 $v$ 出发，能到达的编号最大的点。现在请求出 $A(1),A(2),\dots,A(N)$ 的值。

## 输入格式
第 $1$ 行 $2$ 个整数 $N,M$，表示点数和边数。
接下来 $M$ 行，每行 $2$ 个整数 $U_i,V_i$，表示边 $(U_i,V_i)$。点用 $1,2,\dots,N$ 编号。

## 输出格式
一行 $N$ 个整数 $A(1),A(2),\dots,A(N)$。

## 说明/提示
- 对于 $60\%$ 的数据，$1 \leq N,M \leq 10^3$。
- 对于 $100\%$ 的数据，$1 \leq N,M \leq 10^5$。
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#define MAX 100001

int visited[MAX]={0};
int endlist[MAX];

typedef struct node{
	int pos;
	struct node *next;
} node;

node *list[MAX]={NULL};

void enlist(int x,int y)
{
	node *newnode=(node *)malloc(sizeof(node));
	node *curr=list[x];
	newnode->next=curr;
	newnode->pos=y;
	list[x]=newnode;
	return ;
}

int find(int x)
{
	node *curr=list[x];
	while (curr!=NULL&&visited[curr->pos]==true){
		curr=curr->next;
	}
	if (curr==NULL) return -1;
	else return curr->pos;
}

void DFS(int n,int end)
{	
	if (visited[n]==0){
		visited[n]=1;
		int m;
		while ((m=find(n))!=-1){
			DFS(m,end);
		}
		endlist[n]=end;
	}
	else return ;
}

int main(void)
{
	int N,M;
	scanf("%d %d",&N,&M);
	while (M--){
		int x,y;
		scanf("%d %d",&y,&x);
		enlist(x,y);
	}
	for (int i=N;i>=1;i--){
		DFS(i,i);
	}
	for (int i=1;i<=N;i++){
		if (i-1) printf(" ");
		printf("%d",endlist[i]);
	}
	return 0;
}





















