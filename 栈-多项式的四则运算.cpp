/*
给定一道没有括号的四则混合运算算术题（可能包含多余的空格），请编程计算出结果。运算规则如下：

既有乘、除法又有加、减法的，要先算乘除法，再算加减法；
同级运算时，要从左往右按顺序计算；
所有除法运算的结果都只保留整数部分（直接舍弃小数部分）。
例如：当算术题为 2+3?4?10/6+1/2?4 时：
优先计算乘除法，有 3?4=12，10/6=1，1/2?4=0；
然后计算加减法，2+3?4?10/6+1/2?4=2+12?1+0=13，故输出 13。
输入格式
输入一个字符串，表示算术题：
字符串长度 5≤长度 ≤100000；
字符串中只包含数字字符以及 +，-，*，/ 运算符；
不含括号，可能包含空格；
算式中的运算数范围：1≤ 运算数 ≤200。
输出格式
输出一个整数，表示算术题的计算结果。题目数据保证算式的每一步运算的结果都在 -2×10^9～2×10^9之间。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char ch;
	long int figur;
	struct node *next;
} node;

char *readnum(char *p,long int *a)
{
	long int result=0;
	while (*p>='1'&&*p<='9'){
		result=result*10+*p-'0';
		p++;
	}
	*a=result;
	return p;
}

void push_ch(node *list,char *p){
	node *temp=NULL;
	temp=(node *)malloc(sizeof(node));
	temp->ch=*p;
	temp->next=list->next;
	list->next=temp;
}

void push_num(node *list,long int x){
	node *temp=NULL;
	temp=(node *)malloc(sizeof(node));
	temp->figur=x;
	temp->next=list->next;
	list->next=temp;
}

char pop_ch(node *list)
{
	node *dele,*prev;
	dele=list->next;
	prev=list->next;
	char result=dele->ch;
	list->next=prev;
	free(dele);
	return result;
}

long int pop_num(node *list)
{
	node *dele,*prev;
	dele=list->next;
	prev=list->next;
	long int result=dele->figur;
	list->next=prev;
	free(dele);
	return result;
}

int main(void)
{
	char s[114514];
	gets(s);
	char *p=s;
	int first=1;
	node *figure=NULL;
	node *add=NULL;
	figure=(node *)malloc(sizeof(node));
	add=(node *)malloc(sizeof(node));
	while (*p!='\0'){
		if (first==1&&*p>='1'&&*p<='9'){
			first=0;
			push_ch(add,p++);
		}
		else first=0;
		if (*p==' ') p++;
		else if (*p=='+'||*p=='-') push_ch(add,p++);
		else if (*p>='1'&&*p<='9'){
			long int a,b;
			p=readnum(p,&a);
			while (*p=='*'||*p=='/'){
				if (*p=='*'){
					p++;
					p=readnum(p,&b);
					a*=b;
				}
				else {
					p++;
					p=readnum(p,&b);
					a/=b;
				}
			}
			push_num(figure,a);
		}
	}
	long int sum=0;
	while (figure->next!=NULL){
		char x=pop_ch(add);
		if (x=='+') sum+=pop_num(figure);
		else sum-=pop_num(figure);
	}
	printf("%ld",sum);
	return 0;
}







