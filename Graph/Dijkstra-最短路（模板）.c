/*
题目描述
如题，给出一个有向图，请输出从某一点出发到所有点的最短路径长度。

输入格式
第一行包含三个整数 n,m,s，分别表示点的个数、有向边的个数、出发点的编号。
接下来 m 行每行包含三个整数 u,v,w，表示一条 u→v 的，长度为 w 的边。

输出格式
输出一行 n 个整数，第 i 个表示 s 到第 i 个点的最短路径，若不能到达则输出 2^31-1。
*/

#include <stdio.h>
#define INF 2147483647

int main(void)
{
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    int graph[n+1][n+1];
    int dis[n+1];
    int visited[n+1];
    
    // 初始化
    for (int i = 1; i <= n; i++) {
        dis[i] = INF;
        visited[i] = 0;  // 所有节点初始未访问
    }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            graph[i][j] = INF;
            
    // 读入边信息，处理重边
    for (int i = 1; i <= m; i++) {
        int start, end, len;
        scanf("%d %d %d", &start, &end, &len);
        if (len < graph[start][end]) {  // 处理重边，取最小值
            graph[start][end] = len;
        }
    }
    
    // 关键修正：只设置距离，不标记访问
    dis[s] = 0;
    
    // 主循环
    for (int i = 1; i <= n; i++) {
        int curr = -1;
        
        // 选择当前未访问节点中距离最小的
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (curr == -1 || dis[j] < dis[curr])) {
                curr = j;
            }
        }
        
        // 如果没有可达的未访问节点，提前结束
        if (curr == -1 || dis[curr] == INF) break;
        
        // 关键修正：在这里才标记为已访问
        visited[curr] = 1;
        
        // 更新邻居节点的距离
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && graph[curr][j] != INF) {
                // 防止整数溢出
                if (dis[curr] < INF - graph[curr][j]) {
                    int new_dist = dis[curr] + graph[curr][j];
                    if (new_dist < dis[j]) {
                        dis[j] = new_dist;
                    }
                }
            }
        }
    }
    
    // 输出结果
    for (int i = 1; i <= n; i++) {
        printf("%d", dis[i]);
        if (i < n) printf(" ");
    }
    
    return 0;
}
