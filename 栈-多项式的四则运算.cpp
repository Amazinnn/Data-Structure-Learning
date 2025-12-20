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

int mult=0,flag=1;

typedef struct node{
	long int num;
	struct node *next;
} node;

long int scan(char **p)									//读取数据，并且可以忽略多余的空格，并将p的位置定位至下一个操作符 
{
	char *ps=*p;
	long int sum=0;
	while (*ps==' '||(*ps>='0'&&*ps<='9')){
		if (*ps==' ') ps++;
		else {
			int digit=*ps-'0';
			sum=sum*10+digit;
		}
	}
	*p=ps;
	sum*=flag;
	if (flag==-1) flag*=-1;
	return sum;
}

void push(node *head,long int x)
{
	node *prev=head->next,*temp=NULL;
	temp=(node *)malloc(sizeof(node));
	temp->num=x;
	head->next=temp;
	temp->next=prev;
}

void multi(long int x,node *head)
{
	node *temp=head->next;
	if (mult==1) temp->num*=x;
	else temp->num/=x;
}

long int pop(node *head)
{
	node *del=head->next,*prev=del->next;
	long int result=del->num;
	head->next=prev;
	free(del);
	return result;
}


int main(void)
{
	char s[100010];
	gets(s);
	char *p=s;
	node *head=NULL;
	head=(node *)malloc(sizeof(node));
	head->next=NULL;
	while (*p!='\0'){
		if (*p==' ')p++;
		else if (*p=='*'){
			mult=1;
			p++;
		} 
		else if (*p=='/'){
			mult=-1;
			p++;
		}
		else if(*p=='+'){
			mult=0;
			p++;
		}
		else if (*p=='-'){
			flag=-1;
			mult=0;
			p++;
		}
		else {
			long int num=scan(&p);
			if (mult==0){
				push(head,num);
			}
			else {
				multi(num,head);
			}
		}
	}
	long int result=0;
	while (head->next=NULL){
		result+=pop(head);
	}
	printf("%ld",result);
	return 0;
}









