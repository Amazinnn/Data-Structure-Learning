/*
给定只由 6 种括号字符组成的字符串：(, ), [, ], {, }。
判断每个字符串是否为“合法括号序列”，合法则输出 YES，否则输出 NO。
合法括号序列的定义：
空串合法；
若 A 合法，则 (A), [A], {A} 均合法；
若 A 与 B 均合法，则 AB 合法。
输入格式
第一行一个整数 T，表示数据组数。接下来 T 行，每行一个只包含上述 6 种字符的字符串。

输出格式
对于每个字符串，输出一行：

若其为合法括号序列，输出 YES；
否则输出 NO。
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{								//创建用于构建缓冲区的链表节点 
	char ch;
	struct node *last;
	struct node *next;
} node;

void add(node *buffer,node *p)
{
	char c=p->ch;
	if (c=='(') p->ch=')';
	else if (c=='[') p->ch=']';
	else p->ch='}';						//替换为需要出现的左开口括号，便于之后判断条件的书写 
	if (buffer->next==NULL){
		buffer->next=p;
		p->last=buffer;
	}
	else {
		node *prev=buffer->next;
		buffer->next=p;
		p->last=buffer;
		p->next=prev;
		prev->last=p;
	}
}

void delet(node *buffer)
{
	node *del=buffer->next,*prev=del->next;
	if (prev!=NULL){
	buffer->next=prev;
	prev->last=buffer;
	free(del);
	}
	else {
		free(del);
		buffer->next=NULL;
	}
}


int main(void)
{
	long int T;
	scanf("%ld",&T);getchar();
	for (long int i=1;i<=T;i++){
		char s[1000001];
		gets(s);
		bool valid=1;
		node *buffer=NULL;
		buffer=(node *)malloc(sizeof(node));
		buffer->next=buffer->last=NULL;
		char *p=s;
		while (*p!='\0'){
			if (*p=='('||*p=='['||*p=='{'){
				node *temp=NULL;
				temp=(node *)malloc(sizeof(node));
				temp->ch=*p;
				temp->last=temp->next=NULL;
				add(buffer,temp);
			}
			else {
				if (buffer->next!=NULL&&*p==(buffer->next)->ch){	//缓冲区仍存在待匹配的括号，且恰好匹配成功 
					delet(buffer);
				}
				else {
					valid=false;
					break;
				}
			}
			p++;
		}
		if (buffer->next!=NULL) valid=0;		//如果还有右开口的括号未匹配完，则非法 
		if (valid==true) printf("YES\n");
		else printf("NO\n");
	}
	return 0; 
}
