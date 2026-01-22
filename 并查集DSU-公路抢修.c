/*
# P1111 修复公路

## 题目背景

A 地区在地震过后，连接所有村庄的公路都造成了损坏而无法通车。政府派人修复这些公路。

## 题目描述

给出 A 地区的村庄数 $N$，和公路数 $M$，公路是双向的。并告诉你每条公路的连着哪两个村庄，并告诉你什么时候能修完这条公路。问最早什么时候任意两个村庄能够通车，即最早什么时候任意两条村庄都存在至少一条修复完成的道路（可以由多条公路连成一条道路）。

## 输入格式

第 $1$ 行两个正整数 $N,M$。

下面 $M$ 行，每行 $3$ 个正整数 $x,y,t$，告诉你这条公路连着 $x,y$ 两个村庄，在时间 $t$ 时能修复完成这条公路。

## 输出格式

如果全部公路修复完毕仍然存在两个村庄无法通车，则输出 $-1$，否则输出最早什么时候任意两个村庄能够通车。

## 输入输出样例 #1

### 输入 #1

```
4 4
1 2 6
1 3 4
1 4 5
4 2 3
```

### 输出 #1

```
5
```

## 说明/提示

$1\leq x, y\leq N \le 10 ^ 3$，$1\leq M, t \le 10 ^ 5$。
*/
#include <stdio.h>
#include <stdlib.h>
#define VILLAGE 1001
#define MOD 100001

int set[VILLAGE];
typedef struct node{
	int a;
	int b;
	struct node *next;
} node;
node *list[MOD]={NULL};

void Initialize(void)
{
	for (int i=1;i<=VILLAGE;i++)
		set[i]=i;
}
int Find(int x)
{
	if (set[x]==x) return x;
	else return set[x]=Find(set[x]);
}

void Union(int x,int y)
{
	int rootx=Find(x),
		rooty=Find(y);
	if (rootx!=rooty)
		set[rootx]=rooty;
}

void Insert(int a, int b, int time) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->a = a;
    newNode->b = b;
    newNode->next = list[time];  // 直接指向当前头节点
    list[time] = newNode;        // 新节点成为头节点
}

void Link(int time)
{
	node *curr=list[time];
	if (curr==NULL) return ;
	while (curr!=NULL){
		//printf("%d and %d\n",curr->a,curr->b);
		Union(curr->a,curr->b);
		//printf("%d and %d\n",curr->a,curr->b);
		curr=curr->next;
	}
	return ;
}

int main(void)
{
	int N,M;
	scanf("%d %d",&N,&M);	//村庄数N，道路数M 
	Initialize();
	for (int i=1;i<=M;i++){
		int a,b,time;
		scanf("%d %d %d",&a,&b,&time);
		//printf("Insert %d %d %d\n",a,b,time);
		Insert(a,b,time);
	}
	for (int i=1;i<=MOD;i++){
		//printf("time is %d\n",i);
		if (list[i]==NULL) continue;
		Link(i);
		if (N==1){
			printf("%d",i);
			return 0;
		}
		int vill=0;
		for (int j=1;j<=N;j++){
			if (Find(j)==j)
				vill++;
		}
		if (vill==1){
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}





