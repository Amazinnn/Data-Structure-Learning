/*
# P1102 A-B 数对

## 题目背景

出题是一件痛苦的事情！

相同的题目看多了也会有审美疲劳，于是我舍弃了大家所熟悉的 A+B Problem，改用 A-B 了哈哈！

## 题目描述

给出一串正整数数列以及一个正整数 $C$，要求计算出所有满足 $A - B = C$ 的数对的个数（不同位置的数字一样的数对算不同的数对）。

## 输入格式

输入共两行。

第一行，两个正整数 $N,C$。

第二行，$N$ 个正整数，作为要求处理的那串数。

## 输出格式

一行，表示该串正整数中包含的满足 $A - B = C$ 的数对的个数。

## 输入输出样例 #1

### 输入 #1

```
4 1
1 1 2 3

```

### 输出 #1

```
3
```

## 说明/提示

对于 $75\%$ 的数据，$1 \leq N \leq 2000$。

对于 $100\%$ 的数据，$1 \leq N \leq 2 \times 10^5$，$0 \leq a_i <2^{30}$，$1 \leq C < 2^{30}$。

2017/4/29 新添数据两组
*/

#include <stdio.h>
#include <stdlib.h>

#define MOD 200003

typedef struct ListNode{
	long long int key;
	int time;
	struct ListNode *next;
} ListNode;

int Hash(long long int num)
{
	return (num%MOD +MOD)%MOD;
}

ListNode *list[MOD]={NULL};

void InsertOrUpdate(long long int key)
{
	int index=Hash(key);
	ListNode *curr=list[index];
	while (curr!=NULL){
		if (curr->key==key){
			curr->time++;
			return ;
		}
		curr=curr->next;
	}
	curr=(ListNode *)malloc(sizeof(ListNode));
	curr->key=key;
	curr->time=1;
	curr->next=list[index];
	list[index]=curr;
	return ;	
}

int Find(long long int key)
{
	int index=Hash(key);
	ListNode *curr=list[index];
	while (curr!=NULL){
		if (curr->key==key){
			return curr->time;
		}
		curr=curr->next;
	}
	return 0;
}

void Free(void)
{
	ListNode *curr,*prev;
	for (int i=0;i<MOD;i++){
		curr=list[i];
		while (curr!=NULL){
			prev=curr;
			curr=curr->next;
			free(prev);
		}
	}
	return ;
}

int main(void)
{
	int N;
	long long int C,ans=0;
	scanf("%d %lld",&N,&C);
	long long int num[N];
	for (int i=0;i<N;i++){
		scanf("%lld",&num[i]);
		InsertOrUpdate(num[i]);
	}
	for (int i=0;i<N;i++){
		long long int A=num[i]+C;
		ans+=Find(A);
	}
	printf("%lld",ans);
	Free();
	return 0;
}













