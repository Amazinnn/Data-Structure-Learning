/*
# P1044 [NOIP 2003 普及组] 栈

## 题目背景

栈是计算机中经典的数据结构，简单的说，栈就是限制在一端进行插入删除操作的线性表。
栈有两种最重要的操作，即 pop（从栈顶弹出一个元素）和 push（将一个元素进栈）。
栈的重要性不言自明，任何一门数据结构的课程都会介绍栈。
宁宁同学在复习栈的基本概念时，想到了一个书上没有讲过的问题，而他自己无法给出答案，所以需要你的帮忙。
宁宁考虑的是这样一个问题：一个操作数序列，$1,2,\ldots ,n$（图示为 1 到 3 的情况），栈 A 的深度大于 $n$。
现在可以进行两种操作，
1. 将一个数，从操作数序列的头端移到栈的头端（对应数据结构栈的 push 操作）
2. 将一个数，从栈的头端移到输出序列的尾端（对应数据结构栈的 pop 操作）
使用这两种操作，由一个操作数序列就可以得到一系列的输出序列。 

你的程序将对给定的 $n$，计算并输出由操作数序列 $1,2,\ldots,n$ 经过操作可能得到的输出序列的总数。

## 输入格式
输入文件只含一个整数 $n$（$1 \leq n \leq 18$）。

## 输出格式
输出文件只有一行，即可能输出序列的总数目。


NOIP 2003 普及组第三题
*/

#include <stdio.h>

long long int dp[30][30]={0};

long long int dfs(int i/*栈*/,int j/*队列*/)
{
	if (j==0) return 1;
	else if (dp[i][j]) return dp[i][j];
	else {
		long long int result;
		if (i==0) result=dfs(i+1,j-1);			//栈空，只能进栈 
		else result=dfs(i-1,j)+dfs(i+1,j-1);	//栈非空，可进可出
		dp[i][j]=result;
		return result; 
	}
}



int main(void)
{
	long int n;
	scanf("%ld",&n);
	printf("%lld",dfs(0,n));
	return 0;
}



/*
初版 

#include <stdio.h>

long int count=0;

long int stack(long int inStack,long int inQueue)
{
	printf("队列中等待的:%d，栈中的：%d，递归次数:%d\n",inQueue,inStack,++count);
	if (inStack+inQueue==1) return 1;
	else if (inStack==0) return stack(1,inQueue-1);
	else if (inQueue==0) return 1;
	else return stack(inStack-1,inQueue)+stack(inStack+1,inQueue-1);
}

int main(void)
{
	long int n;
	scanf("%ld",&n);
	printf("%ld",stack(0,n));
	return 0;
}
*/







