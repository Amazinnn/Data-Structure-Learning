/*
题目描述
如题，给出一个无向图，求出最小生成树，
如果该图不连通，则输出 orz。

输入格式
第一行包含两个整数 N,M，表示该图共有 N 个结点和 M 条无向边。

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int a;
	int b;
	int len;
} Edge;

void MidToLeft(Edge *edges,int n)
{
	if (edges[0].len>edges[n/2].len) Swap(&edges[0],&edges[n/2]);
	if (edges[n/2].len>edges[n-1].len) Swap(&edges[n/2],&edges[n-1]);
	if (edges[n/2].len>edges[0].len) Swap(&edges[0],&edges[n/2]);
}

int Find(int *parent,int x)
{
	if (parent[x]==x) return x;
	return parent[x]=Find(parent,parent[x]);
}

void Sort(Edge *edges, int n) {
    if (n <= 1) return;

    // 1. 优化：将中间元素换到最左边，作为基准值，避免最坏情况
    MidToLeft(edges, n); 

    int low = 0;
    int high = n - 1;
    // 关键：在交换元素前，先固定保存基准值本身，而不是其索引
    Edge pivot_value = edges[0]; 

    // 2. 分区过程："挖坑填数"
    while (low < high) {
        // 2.1 从右向左找：第一个 <= pivot_value 的元素
        while (low < high && edges[high].len > pivot_value.len) high--;
        if (low < high) {
            // 找到后，将其填入左边的"坑"(edges[low])，同时 high 位置成为新"坑"
            edges[low] = edges[high]; 
            low++;
        }

        // 2.2 从左向右找：第一个 > pivot_value 的元素
        while (low < high && edges[low].len <= pivot_value.len) low++;
        if (low < high) {
            // 找到后，将其填入右边的"坑"(edges[high])，同时 low 位置成为新"坑"
            edges[high] = edges[low]; 
            high--;
        }
    }
    // 3. 分区结束：low == high，此处即为基准值的最终位置
    edges[low] = pivot_value; 

    // 4. 递归排序左右子区间
    Sort(edges, low);                 // 排序左半部分 (elements < pivot_value)
    Sort(edges + low + 1, n - low - 1); // 排序右半部分 (elements > pivot_value)
}

long int kruskal(Edge *edges,int n,int m)
{
	long int ans=0;		// 最小生成树的总权值
	int link=0;		// 当前已选中的边数
	int parent[n+1];		// 并查集数组，编号从1到n
	
	// 初始化并查集，每个节点自成一个集合[1,3](@ref)
	for (int i=1;i<=n;i++){
		parent[i]=i;
	}
	
	// 将边按权值从小到大排序[1,3](@ref)
	Sort(edges,m);
	
	// 遍历所有边，按权值从小到大处理[1,6](@ref)
	for (int i=0;i<m;i++){
		// 查找当前边两个端点的根节点[1,3](@ref)
		int rootx=Find(parent,edges[i].a),
			rooty=Find(parent,edges[i].b);
			
		// 如果两端点不在同一集合，加入最小生成树[1,6](@ref)
		if (rootx!=rooty){
			parent[rootx]=rooty;	// 合并两个集合
			ans+=edges[i].len;	// 累加边权值
			link++;		// 已选边数加1
		}
		
		// 已形成最小生成树（n-1条边），提前结束[1,3](@ref)
		if (link>=n-1) break;
	}
	
	// 检查图是否连通：能形成生成树则返回总权值，否则返回-1[1,4](@ref)
	if (link==n-1) return ans;
	else return -1;
}

int main(void)
{
	int n,m;
	scanf("%d %d",&n,&m);
	Edge edges[m];
	for (int i=0;i<m;i++)
		scanf("%d %d %d",
		&edges[i].a,&edges[i].b,&edges[i].len);
	long int ans=kruskal(edges,n,m);
	if (ans==-1) printf("orz");
	else printf("%ld",ans);
	return 0;
}






