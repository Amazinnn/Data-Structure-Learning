/*
# P4305 [JLOI2011] 不重复数字

## 题目描述

给定 $n$ 个数，要求把其中重复的去掉，只保留第一次出现的数。

## 输入格式

**本题有多组数据。**

第一行一个整数 $T$，表示数据组数。

对于每组数据：

第一行一个整数 $n$。

第二行 $n$ 个数，表示给定的数。

## 输出格式

对于每组数据，输出一行，为去重后剩下的数，两个数之间用一个空格隔开。

## 输入输出样例 #1

### 输入 #1

```
2
11
1 2 18 3 3 19 2 3 6 5 4
6
1 2 3 4 5 6

```

### 输出 #1

```
1 2 18 3 19 6 5 4
1 2 3 4 5 6

```

## 说明/提示

对于 $30\%$ 的数据，$n \le 100$，给出的数 $\in [0, 100]$。

对于 $60\%$ 的数据，$n \le 10^4$，给出的数 $\in [0, 10^4]$。

对于 $100\%$ 的数据，$1 \le T\le 50$，$1 \le n \le 5 \times 10^4$，给出的数在 $32$ 位有符号整数范围内。
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MOD 100007
#define SEED 31

typedef struct node{
	char *key;
	bool occupy;
} node;

int Hash(char *s)
{
	int length=strlen(s),hash=0;
	for (int i=0;i<length;i++){
		hash=(hash*SEED+s[i]-'0')%MOD;
	}
	return hash;
}

void Insert(node *list,char *s)
{
	int OriginPos=Hash(s),
		i=0,
		CurrPos=OriginPos;
	while (list[CurrPos].occupy==true){
		i++;
		CurrPos=OriginPos+pow(-1,i+1)*((i+1)/2);
		while (CurrPos<0) CurrPos+=MOD;
	}
	list[CurrPos].key=(char *)malloc(33*sizeof(char));
	strcpy(list[CurrPos].key,s);
	list[CurrPos].occupy=true;
	return ;
}

bool Find(node *list,char *s)
{
	int OriginPos=Hash(s),
		i=0,
		CurrPos=OriginPos;
	while (list[CurrPos].occupy==true){
		if (strcmp(list[CurrPos].key,s)==0)
			return true;
		i++;
		CurrPos=OriginPos+pow(-1,i+1)*((i+1)/2);
		while (CurrPos<0) CurrPos+=MOD;
	}
	return false;
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for (int i=1;i<=T;i++){
		int length;
		bool first=true;
		scanf("%d",&length);
		node list[MOD]={{NULL,false}};
		for (int j=0;j<length;j++){
			char s[33];
			scanf("%s",s);
			if(!Find(list,s)){
				Insert(list,s);
				if (first)
					first=false;
				else
					printf(" ");
				printf("%s",s);
			}
		}
		printf("\n");
	}
	return 0;
}





