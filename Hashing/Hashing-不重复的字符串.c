/*
# P3370 【模板】字符串哈希

## 题目描述

如题，给定 $N$ 个字符串（第 $i$ 个字符串长度为 $M_i$，字符串内包含数字、大小写字母，大小写敏感），请求出 $N$ 个字符串中共有多少个不同的字符串。


**友情提醒：如果真的想好好练习哈希的话，请自觉。**

## 输入格式

第一行包含一个整数 $N$，为字符串的个数。

接下来 $N$ 行每行包含一个字符串，为所提供的字符串。

## 输出格式

输出包含一行，包含一个整数，为不同的字符串个数。

## 输入输出样例 #1

### 输入 #1

```
5
abc
aaaa
abc
abcc
12345
```

### 输出 #1

```
4
```

## 说明/提示

### 数据范围

对于 $30\%$ 的数据：$N\leq 10$，$M_i≈6$，$M_{\max}\leq 15$。

对于 $70\%$ 的数据：$N\leq 1000$，$M_i≈100$，$M_{\max}\leq 150$。

对于 $100\%$ 的数据：$N\leq 10000$，$M_i≈1000$，$M_{\max}\leq 1500$。

### 样例说明

样例中第一个字符串 $\tt{abc}$ 和第三个字符串 $\tt{abc}$ 是一样的，所以所提供字符串的集合为 $\{\tt{aaaa},\tt{abc},\tt{abcc},\tt{12345}\}$，故共计 $4$ 个不同的字符串。

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10003
#define SEED 31 

typedef struct ListNode{
	char *s;
	struct ListNode *next;
} ListNode;

ListNode *list[MOD]={NULL};
int total=0;

int Hash(char *s)
{
	int length=strlen(s);
	int hash=0;
	for (int i=0;i<length;i++){
		hash=(hash*SEED+s[i])%MOD;
	}
	return hash;
}

void InsertOrUpdate(char *s)
{
	int index=Hash(s);
	ListNode *curr=list[index];
	while (curr!=NULL){
		if (strcmp(curr->s,s)==0){
			return ;
		}
		curr=curr->next;
	}
	curr=(ListNode *)malloc(sizeof(ListNode));
	curr->s=s;
	curr->next=list[index];
	list[index]=curr;
	total++;
	return ;	
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
	scanf("%d",&N);
	getchar();
	char Str[N][1510];
	for (int i=0;i<N;i++){
		scanf("%s",Str[i]);
		getchar();
		InsertOrUpdate(Str[i]);
	}
	printf("%d",total);
	Free();
	return 0;
}
