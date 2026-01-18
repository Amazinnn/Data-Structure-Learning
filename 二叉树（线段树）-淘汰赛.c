/*
有 2的n次方（n≤7）个国家参加世界杯决赛圈且进入淘汰赛环节。
已经知道各个国家的能力值，且都不相等。
能力值高的国家和能力值低的国家踢比赛时高者获胜。
1 号国家和 2 号国家踢一场比赛，胜者晋级。3 号国家和 4 号国家也踢一场，胜者晋级……
晋级后的国家用相同的方法继续完成赛程，直到决出冠军。
给出各个国家的能力值，请问亚军是哪个国家？

输入格式
第一行一个整数 n，表示一共 2^n个国家参赛。
第二行 2^n个整数，第 i 个整数表示编号为 i 的国家的能力值（1≤i≤2^n ，能力值在 int 范围内）。
数据保证不存在平局。

输出格式
仅一个整数，表示亚军国家的编号。
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
	int num;
	int level;
	struct node *next1;
	struct node *next2;
} node;

node *stack[200];
int stacktop=0;
int n;
int total;

void competition(void)
{
	int a,b;
	int count=0;
	for (int i=0;i<total;i++){
		if (stack[i]!=NULL&&count==0){
			count++;
			a=i;
			continue;
		}
		else if(stack[i]!=NULL&&count==1){
			count=0;
			b=i;
			node *p1=stack[a],*p2=stack[b];
			if (p1->level>p2->level){			//总之胜者的右子代一定是自己，左子代是被打败者 
				p1->next1=p2;
				p1->next2=p1;
				stack[b]=NULL;
			}
			else {
				p2->next1=p1;
				p2->next2=p2;
				stack[a]=NULL;
			}
		}
		else ;
	}
}

int main(void)
{
	scanf("%d",&n);
	total=pow(2,n);
	for (int i=0;i<total;i++){
		node *temp=NULL;
		temp=(node *)malloc(sizeof(node));
		temp->num=i+1;
		scanf("%d",&temp->level);
		temp->next1=temp->next2=NULL;
		stack[i]=temp;
	}
	stacktop=total;
	node *winner=NULL;
	for (int i=1;i<=n;i++) competition();		//重复n轮比赛，决出最终胜负 
	for (int j=0;j<total;j++){
		if (stack[j]!=NULL){
			winner=stack[j];
			break;
		}
	}
	winner=winner->next1;
	printf("%d",winner->num);
	return 0;
}


/*
#include <stdio.h>
#include <math.h>

// 全局数组存储选手能力值，索引从1开始使用以匹配原代码逻辑
int a[(1 << 7) + 1]; // 最大支持n=7，即128名选手
int n;


 * @brief 递归函数，模拟淘汰赛过程，并在最外层调用时返回亚军编号。
 * @param l 当前区间左边界（选手编号起始）
 * @param r 当前区间右边界（选手编号结束）
 * @return 在当前区间内的胜者编号（非最外层调用）或亚军编号（最外层调用）
 
int w(int l, int r) {
    // 递归基线条件：区间只剩一名选手，直接返回其编号
    if (l == r) {
        return l;
    }
    
    int mid = (l + r) / 2;
    // 递归处理左半区间并获取胜者
    int ll_winner = w(l, mid);
    // 递归处理右半区间并获取胜者
    int rr_winner = w(mid + 1, r);
    
    // 判断是否为最外层调用（即整个比赛的区间）
    if (l != 1 || r != (1 << n)) {
        // 非最外层调用：选择能力值较高的选手晋级
        if (a[ll_winner] > a[rr_winner]) {
            return ll_winner;
        } else {
            return rr_winner;
        }
    } else {
        // 最外层调用（决赛）：选择能力值较低的选手作为亚军返回
        if (a[ll_winner] < a[rr_winner]) {
            return ll_winner;
        } else {
            return rr_winner;
        }
    }
}

int main() {
    // 读取参赛国家数量n
    scanf("%d", &n);
    int total = 1 << n; // 计算总选手数：2^n
    
    // 读取每个国家的能力值，存储到数组a中，索引从1开始
    for (int i = 1; i <= total; i++) {
        scanf("%d", &a[i]);
    }
    
    // 调用递归函数，从整个区间开始计算，最终返回亚军编号
    int result = w(1, total);
    printf("%d\n", result);
    
    return 0;
}
*/







