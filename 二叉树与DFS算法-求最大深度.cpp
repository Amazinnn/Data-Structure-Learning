/*
题目描述
有一个 n(n≤10^6) 个结点的二叉树。
给出每个结点的两个子结点编号（均不超过 n），
建立一棵二叉树（根节点的编号为 1），如果是叶子结点，则输入 0 0。
建好这棵二叉树之后，请求出它的深度。
二叉树的深度是指从根节点到叶子结点时，最多经过了几层。

输入格式
第一行一个整数 n，表示结点数。
之后 n 行，第 i 行两个整数 l、r，分别表示结点 i 的左右子结点编号。
若 l=0 则表示无左子结点，r=0 同理。

输出格式
一个整数，表示最大结点深度。
*/

/*
事实上，本题采用广度优先算法更好，因其避免栈帧溢出 
*/ 


#include <stdio.h>

typedef struct node{
	long int next1;
	long int next2;
} node;

node Stack[100000]={0};
long int maxdepth=1;

void search(node leaf,long int depth)
{
	if (leaf.next1==0&&leaf.next2==0){
		if (depth>maxdepth) maxdepth=depth;
		return ;
	}
	else {
		if (leaf.next1!=0){
			search(Stack[leaf.next1],depth+1);
		}
		if (leaf.next2!=0){
			search(Stack[leaf.next2],depth+1);
		}
		return ;
	}
}

int main(void)
{
	long int n;
	scanf("%ld",&n);
	for (long int i=1;i<n;i++){				//数组下标i,对应编号i
		node temp;
		long int n1,n2;
		scanf("%ld %ld",&n1,&n2);
		temp.next1=n1;
		temp.next2=n2;
		Stack[i]=temp;
	}
	search(Stack[1],1);
	printf("%ld",maxdepth);
	return 0;
}





