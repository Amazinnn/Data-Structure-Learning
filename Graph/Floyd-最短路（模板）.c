/*
# B3647 【模板】Floyd

## 题目描述
给出一张由 $n$ 个点 $m$ 条边组成的无向图。
求出所有点对 $(i,j)$ 之间的最短路径。

## 输入格式
第一行为两个整数 $n,m$，分别代表点的个数和边的条数。
接下来 $m$ 行，每行三个整数 $u,v,w$，代表 $u,v$ 之间存在一条边权为 $w$ 的边。

## 输出格式
输出 $n$ 行每行 $n$ 个整数。
第 $i$ 行的第 $j$ 个整数代表从 $i$ 到 $j$ 的最短路径。

对于 $100\%$ 的数据，$n \le 100$，$m \le 4500$，
任意一条边的权值 $w$ 是正整数且 $1 \leqslant w \leqslant 1000$。
**数据中可能存在重边。**
*/

#include <stdio.h>
#define INF 0x3f3f3f3f  // 定义无穷大值，0x3f3f3f3f是一个较大的数，且两倍不会溢出int，适合做距离的初始值

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);  // 读入顶点数n和边数m
    
    // 声明距离矩阵dis和路径矩阵path
    int dis[n][n], path[n][n];
    
    // 初始化距离矩阵和路径矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 初始化路径矩阵：记录从i到j的最短路径中，i的第一个后继节点
            // 初始时，如果i和j之间有边，则认为下一个节点是j（之后会更新）
            // 这里初始化为j，表示从i出发下一步是j（若i==j，则path[i][j]=i）
            path[i][j] = j;
            
            // 初始化距离矩阵：主对角线（自己到自己的距离）为0，其他为无穷大
            if (i == j) 
                dis[i][j] = 0;
            else 
                dis[i][j] = INF;
        }
    }
    
    // 读入m条边，构建初始邻接矩阵
    for (int i = 1; i <= m; i++) {
        int x, y, len;
        scanf("%d %d %d", &x, &y, &len);
        x--, y--;  // 将输入的顶点编号（从1开始）转换为从0开始的数组下标
        
        // 处理重边：只保留最短的边
        // 因为是无向图，所以需要同时更新dis[x][y]和dis[y][x]
        if (dis[x][y] > len) 
            dis[x][y] = dis[y][x] = len;
    }
    
    // Floyd算法核心：动态规划求解所有顶点对的最短路径
    for (int k = 0; k < n; k++) {           // 枚举中转点k
        for (int i = 0; i < n; i++) {       // 枚举起点i
            for (int j = 0; j < n; j++) {   // 枚举终点j
                // 如果通过中转点k可以使路径更短，则更新距离和路径
                if (dis[i][k] != INF &&     // 防止INF相加溢出
                    dis[k][j] != INF && 
                    dis[i][j] > dis[i][k] + dis[k][j]) {
                    
                    // 更新最短距离
                    dis[i][j] = dis[i][k] + dis[k][j];
                    
                    // 更新路径：从i到j的新路径等于从i到k的路径，再接上k到j的路径
                    // 这里path[i][j]记录的是从i到j的第一个后继节点
                    // 当路径更新为i->...->k->...->j时，i的第一个后继节点应该是原来i到k路径的第一个后继节点
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    
    // 输出最终的距离矩阵
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (t) printf(" ");  // 控制空格格式：每行第一个数前不输出空格
            printf("%d", dis[s][t]);
        }
        printf("\n");  // 每行输出完毕后换行
    }
    return 0;
}











