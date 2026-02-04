/*
# P1216 [IOI 1994 / USACO1.5] 数字三角形 Number Triangles

## 题目描述
写一个程序来查找从最高点到底部任意处结束的路径，
使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。

## 输入格式
第一个行一个正整数 $r$，表示行的数目。
后面每行为这个数字金字塔特定行包含的整数。

## 输出格式
单独的一行，包含那个可能得到的最大的和。

## 说明/提示
【数据范围】  
对于 $100\%$ 的数据，$1\le r\le 1000$，所有输入在 $[0,100]$ 范围内。

IOI1994 Day1T1 / USACO Training Section 1.5。
*/

#include <stdio.h>
#define Max(a,b) ((a)>(b)?(a):(b))

int main(void)
{
	int r;
	scanf("%d",&r);
	int row[r],f[r][r];
	for (int i=0;i<r;i++){
		for (int j=0;j<r;j++){
			if (j<=i) scanf("%d",&row[j]);
			else row[j]=0;
			if (i==0) f[i][j]=row[j];
			else {
				if (j!=0) f[i][j]=Max(f[i-1][j-1],f[i-1][j])+row[j];
				else f[i][j]=f[i-1][j]+row[j];
			}
		}
	}
	long int max=-1;
	for (int i=0;i<r;i++){
		if (f[r-1][i]>max) max=f[r-1][i];
	}
	printf("%ld",max);
	return 0;
}
























