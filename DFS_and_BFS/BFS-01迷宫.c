/*
# P1141 01迷宫

## 题目描述

有一个仅由数字 $0$ 与 $1$ 组成的 $n \times n$ 格迷宫。
若你位于一格 $0$ 上，那么你可以移动到相邻 $4$ 格中的某一格 $1$ 上，
同样若你位于一格 $1$ 上，那么你可以移动到相邻 $4$ 格中的某一格 $0$ 上。

你的任务是：对于给定的迷宫，询问从某一格开始能移动到多少个格子（包含自身）。

## 输入格式

第一行为两个正整数 $n,m$。

下面 $n$ 行，每行 $n$ 个字符，字符只可能是 $0$ 或者 $1$，字符之间没有空格。

接下来 $m$ 行，每行两个用空格分隔的正整数 $i,j$，
对应了迷宫中第 $i$ 行第 $j$ 列的一个格子，询问从这一格开始能移动到多少格。

## 输出格式

$m$ 行，对于每个询问输出相应答案。


## 说明/提示

对于样例，所有格子互相可达。

- 对于 $20\%$ 的数据，$n \leq 10$；
- 对于 $40\%$ 的数据，$n \leq 50$；
- 对于 $50\%$ 的数据，$m \leq 5$；
- 对于 $60\%$ 的数据，$n,m \leq 100$；
- 对于 $100\%$ 的数据，$1\le n \leq 1000$，$1\le m \leq 100000$。
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000000

int maze[1000][1000];
int dir[4][2]={1,0,-1,0,0,1,0,-1};

typedef struct {
	int x;
	int y;
} node;

typedef struct {
	node place[MAX];
	int front;
	int rear;
} Queue;

void Init(Queue *q)
{
	q->front=q->rear=0;
}
void enqueue(Queue *q,int x,int y)
{
	q->place[q->rear].x=x;
	q->place[q->rear].y=y;
	q->rear++;
}

node dequeue(Queue *q)
{
	return q->place[q->front++];
}

bool isEmpty(Queue *q)
{
	return q->front>=q->rear;
}

bool isExceed(node pos,int n)
{
	int x=pos.x,y=pos.y;
	if (x<0||x>=n) return true;
	if (y<0||y>=n) return true;
	return false;
}

long int BFS(int n,int x,int y)
{
	int visited[n][n];
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			visited[i][j]=0;
	long int ans=1;
	Queue *q=(Queue *)malloc(sizeof(Queue));
	Init(q);
	enqueue(q,x,y);
	visited[x][y]=1;
	while (!isEmpty(q)){
		node curr=dequeue(q);
		node next[4];
		for (int i=0;i<4;i++){
			int x_=curr.x+dir[i][0],
				y_=curr.y+dir[i][1];
			if (!isExceed(next[i],n)
			&&!visited[x_][y_]
			&&maze[x][y]!=maze[x_][y_]){
				visited[x_][y_]=1;
				enqueue(q,x_,y_);
				ans++;
			}
		}
	}
	return ans;
}

int main(void)
{
	int n,x,y;
	long int m;
	scanf("%d %ld",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			scanf("%1d",&maze[i][j]);
	while (m--){
		scanf("%d %d",&x,&y);
		x--,y--;
		printf("%ld\n",BFS(n,x,y));
	}
	return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000

int maze[MAX_N][MAX_N];
int parent[MAX_N * MAX_N];  // 并查集父节点数组
int size[MAX_N * MAX_N];    // 每个连通分量的大小
int visited[MAX_N][MAX_N];  // 访问标记
int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
int n;

// 并查集查找（带路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 并查集合并
void unionSets(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA != rootB) {
        if (size[rootA] < size[rootB]) {
            parent[rootA] = rootB;
            size[rootB] += size[rootA];
        } else {
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
        }
    }
}

// 坐标转一维索引
int toIndex(int x, int y) {
    return x * n + y;
}

// 预处理：使用BFS标记所有连通分量
void preprocess() {
    // 初始化并查集
    for (int i = 0; i < n * n; i++) {
        parent[i] = i;
        size[i] = 1;
    }
    
    // 只处理右方向和下方向的连接（避免重复）
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 检查右侧邻居
            if (j + 1 < n && maze[i][j] != maze[i][j+1]) {
                unionSets(toIndex(i, j), toIndex(i, j+1));
            }
            // 检查下侧邻居
            if (i + 1 < n && maze[i][j] != maze[i+1][j]) {
                unionSets(toIndex(i, j), toIndex(i+1, j));
            }
        }
    }
}

int main(void) {
    long int m;
    scanf("%d %ld", &n, &m);
    
    // 读取迷宫
    for (int i = 0; i < n; i++) {
        char row[MAX_N + 1];
        scanf("%s", row);
        for (int j = 0; j < n; j++) {
            maze[i][j] = row[j] - '0';
        }
    }
    
    // 预处理
    preprocess();
    
    // 处理查询
    while (m--) {
        int x, y;
        scanf("%d %d", &x, &y);
        x--; y--;
        int root = find(toIndex(x, y));
        printf("%d\n", size[root]);
    }
    
    return 0;
}




