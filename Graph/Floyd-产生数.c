/*
# P1037 [NOIP 2002 普及组] 产生数

## 题目描述

给出一个整数 $n$ 和 $k$ 个变换规则。

规则：
- 一位数可变换成另一个一位数。
- 规则的右部不能为零。

例如：$n=234,k=2$。有以下两个规则：

- $2\longrightarrow 5$。  
- $3\longrightarrow 6$。 

上面的整数 $234$ 经过变换后可能产生出的整数为（包括原数）:

- $234$。
- $534$。
- $264$。
- $564$。

共 $4$ 种不同的产生数。

现在给出一个整数 $n$ 和 $k$ 个规则。
求出经过任意次的变换（$0$ 次或多次），能产生出多少个不同整数。
仅要求输出个数。

## 输入格式
第一行两个整数 $n,k$，含义如题面所示。
接下来 $k$ 行，每行两个整数 $x_i,y_i$，表示每条规则。

## 输出格式
共一行，输出能生成的数字个数。

## 说明/提示
对于 $100\%$ 数据，满足 $n \lt 10^{30}$，$k \le 15$。

**【题目来源】**
NOIP 2002 普及组第三题
*/

#include <stdio.h>

int graph[10][10];
int num[10]={0};
int possibility[10]={0};
int ans[31];

void Init(void)
{
	for (int i=0;i<=9;i++){
		for (int j=0;j<=9;j++){
			if (i!=j) graph[i][j]=20;
			else graph[i][j]=0;
		}
	}
	int k;
	scanf("%d",&k);
	while (k--){
		int start,end;
		scanf("%d %d",&start,&end);
		graph[start][end]=1;
	}
	for (int i=0;i<=9;i++){
		for (int j=0;j<=9;j++){
			for (int k=0;k<=9;k++){
				if (graph[j][i]!=20&&graph[i][k]!=20&&
				(graph[j][i]+graph[i][k]<graph[j][k])){
					graph[j][k]=graph[j][i]+graph[i][k];
				}
			}
		}
	}
}

void GetNumber(void)
{
	char digit;
	while ((digit=getchar())!=' '){
		if (digit>='0'&&digit<='9'){
			num[digit-'0']++;
		}
	}
}

void Multi(int n)
{
	int add=0;
	for (int i=30;i>=0;i--){
		ans[i]=ans[i]*n+add;
		add=ans[i]/10;
		ans[i]%=10;
	}
}


int main(void)
{
	GetNumber();
	Init();
	for (int i=0;i<=9;i++){
		for (int j=0;j<=9;j++){
			if (graph[i][j]<20) possibility[i]++;
		}
	}
	ans[30]=1;
	for (int i=0;i<=9;i++){
		for(int j=1;j<=num[i];j++){
			Multi(possibility[i]);
		}
	}
	int first=0;
	while (ans[first]==0) first++;
	for (;first<=30;first++){
		printf("%d",ans[first]);
	}
	return 0;
}



















