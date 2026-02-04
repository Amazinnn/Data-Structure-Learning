/*
# P5318 【深基18.例3】查找文献

## 题目描述

小 K 喜欢翻看洛谷博客获取知识。
每篇文章可能会有若干个（也有可能没有）参考文献的链接指向别的博客文章。
小 K 求知欲旺盛，如果他看了某篇文章，那么他一定会去看这篇文章的参考文献
（如果他之前已经看过这篇参考文献的话就不用再看它了）。

假设洛谷博客里面一共有 $n(1\le n\le10^5)$ 篇文章（编号为 $1$ 到 $n$）
以及 $m(1\le m\le10^6)$ 条参考文献引用关系。
目前小 K 已经打开了编号为 1 的一篇文章，请帮助小 K 设计一种方法，
使小 K 可以不重复、不遗漏的看完所有他能看到的文章。

这边是已经整理好的参考文献关系图，其中，文献 $X\to Y$ 表示文章 $X$ 有参考文献 $Y$。
不保证编号为 $1$ 的文章没有被其他文章引用。
请对这个图分别进行 DFS 和 BFS，并输出遍历结果。
如果有很多篇文章可以参阅，请先看编号较小的那篇（因此你可能需要先排序）。

## 输入格式
共 $m+1$ 行，第 $1$ 行为 $2$ 个数，$n$ 和 $m$，
分别表示一共有 $n(1\le n\le10^5)$ 篇文章（编号为 $1$ 到 $n$）以及$m(1\le m\le10^6)$ 条参考文献引用关系。
接下来 $m$ 行，每行有两个整数 $X,Y$ 表示文章 $X$ 有参考文献 $Y$。

## 输出格式
共 $2$ 行。
第一行为 DFS 遍历结果，第二行为 BFS 遍历结果。
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define M 100001

typedef struct node{
	int book;
	struct node *next;
} Node;

typedef struct{
	int queue[M];
	int front,rear;
} Queue;

bool booklist[M];
Node *nodelist[M]={NULL};
Queue q;

void MakeEmpty(void)
{
	for (int i=0;i<M;i++)
		booklist[i]=false;
}

void InitQueue(void)
{
	q.front=q.rear=0;
}

void EnList(int from,int to)
{
	//printf("插入查阅路径：文献%d到文献%d\n",from,to);
	Node *newnode=(Node *)malloc(sizeof(Node));
	newnode->book=to;
	newnode->next=NULL;
	if (nodelist[from]==NULL) nodelist[from]=newnode;
	else if (nodelist[from]->book>to){
		newnode->next=nodelist[from];
		nodelist[from]=newnode;
	}
	else {
		Node *curr=nodelist[from],*prev;
		while (curr!=NULL&&
		curr->book<newnode->book){
			prev=curr;
			curr=curr->next;
		}
		prev->next=newnode;
		newnode->next=curr;
	}
	return ;
}

int FindNext(int num)
{
	Node *curr=nodelist[num];
	while (curr!=NULL&&booklist[curr->book]==true){
		curr=curr->next; 
	}
	if (curr==NULL){
		//printf("文献%d的所有已经查阅完。\n",num);
		return -1;
	}
	else {
		booklist[curr->book]=true;
		//printf("查阅到文献%d。\n",curr->book);
		return curr->book;
	}
}

void Enqueue(int num)
{
	q.queue[q.rear++]=num;
}

int Dequeue(void)
{
	return q.queue[q.front++];
}

bool IsEmpty(void)
{
	return (q.front>=q.rear);
}

void DFS(int num)
{
	printf("%d ",num);
	booklist[num]=true;
	int nextbook;
	while ((nextbook=FindNext(num))!=-1){
		booklist[nextbook]=true;
		DFS(nextbook);
	}
	return ;
}

void BFS(int input)
{
	MakeEmpty();
	InitQueue();
	Enqueue(input);
	booklist[input]=true;
	while (!IsEmpty()){
		int num=Dequeue();
		printf("%d ",num);
		int nextbook;
		while ((nextbook=FindNext(num))!=-1){
			Enqueue(nextbook);
			booklist[nextbook]=true;	
		}
	}
}

int main(void)
{
	int n,m;
	scanf("%d %d",&n,&m);
	while (m--){
		int from,to;
		scanf("%d %d",&from,&to);
		EnList(from,to);
	}
	MakeEmpty();
	DFS(1);
	printf("\n");
	MakeEmpty();
	BFS(1);
	return 0;
}
















