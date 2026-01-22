/*
n 个人围成一圈，从第一个人开始报数,数到 m 的人出列，
再由下一个人重新从 1 开始报数，数到 m 的人再出圈，依
次类推，直到所有的人都出圈，请输出依次出圈人的编号。
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct node{
	int num;
	struct node *next;
	bool called;
} node;

node *create(int n)
{
	node *star=NULL,*p=NULL,*plast=NULL;
	star=(node *)malloc(sizeof(node));
	star->num=1;
	star->called=0;
	plast=star;
	for (int i=2;i<=n;i++){
		p=(node *)malloc(sizeof(node));
		p->next=NULL;
		plast->next=p;
		plast=p;
		p->num=i;
		p->called=0;
	}
	plast->next=star;
	return star;
}

int main(void) {
	int n,m;
	scanf("%d %d",&n,&m);
	node *start=create(n);
	node *p=start;
	for (int i=1;i<=n;i++){
		for (int j=0;;){
			if (p->called==0) j++;
			if (j==m){
				break;
			}
			else {
				p=p->next;
			}
		}
		printf("%d ",p->num);
		p->called=1;
		p=p->next;
	}
    return 0;
}

