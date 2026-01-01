/*
# P1990 覆盖墙壁

## 题目描述

你有一个长为 $N$ 宽为 $2$ 的墙壁，给你两种砖头：一个长 $2$ 宽 $1$，
另一个是 L 型覆盖 $3$ 个单元的砖头。
砖头可以旋转，两种砖头可以无限制提供。
你的任务是计算用这两种来覆盖 $N\times 2$ 的墙壁的覆盖方法。
例如一个 $2\times3$ 的墙可以有 $5$ 种覆盖方法，如下：
```
012 002 011 001 011  
012 112 022 011 001
```
注意可以使用两种砖头混合起来覆盖，如 $2\times4$ 的墙可以这样覆盖：
```
0112
0012
```
给定 $N$，要求计算 $2\times N$ 的墙壁的覆盖方法。
由于结果很大，所以只要求输出最后 $4$ 位。
例如 $2\times 13$ 的覆盖方法为 $13465$，只需输出 $3465$ 即可。
如果答案少于 $4$ 位，就直接输出就可以，不用加前导 $0$，如 $N=3$ 时输出 $5$。

## 输入格式
一个整数 $N$，表示墙壁的长。

## 输出格式
输出覆盖方法的最后 $4$ 位，如果不足 $4$ 位就输出整个答案。

数据保证，$1\leq N\leq 1000000$。
*/



#include <stdio.h>
int dp[1000010]={0,1,2,5};
long int n;

int F(long int x)
{
	if (x==0) return 0;
	else if (dp[x]) return dp[x];
	else {
		dp[x]=(2*F(x-1)+F(x-3))%10000;
		return dp[x];
	}
}

int main(void)
{
	scanf("%ld",&n);
	F(n);
	printf("%d",dp[n]%10000);
	return 0;
}









/*
初版 
#include <stdio.h>
#include <math.h>
#define Max(a,b) ((a>=b)?(a):(b))

long long int count=0;
int n;

void search(int up,int down)
{
	if (up==n&&down==n){
		count++;
		count%=10000;
	}
	else if (up>n||down>n) ;
	else {
		if (up-down>=2) search(up,down+2);
		else if (down-up>=2) search(up+2,down);
		else if (up-down==1){
				search(up+1,down+2);
				search(up,down+2);
		}
		else if (down-up==1){
				search(up+2,down+1);
				search(up+2,down);
		}
		else {
			search(up+1,down+1);
			//search(up+2,down);
			search(up,down+2);
			search(up+1,down+2);
			search(up+2,down+1);
		}
	}
	return ;
}

int main(void)
{
	scanf("%d",&n);
	search(0,0);
	printf("%d",count);
	return 0;
}
*/











