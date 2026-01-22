/*
给出一棵二叉树的中序与后序排列。求出它的先序排列。
（约定树结点用不同的大写字母表示，且二叉树的节点个数 ≤8）。

输入格式
共两行，均为大写字母组成的字符串，表示一棵二叉树的中序与后序排列。

输出格式
共一行一个字符串，表示一棵二叉树的先序。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char inorder[27];
char reorder[27];

void print(int inStart,int reStart,int length)	//输入的是下标，注意从0开始！ 
{
	if (length==0){
		 ;
	}
	else if (length==1){
		printf("%c",inorder[inStart]);
	}
	else {
		int father;
		for (father=inStart;inorder[father]!=reorder[reStart+length-1];father++) ;
		int leftLen=father-inStart;
		printf("%c",inorder[father]);
		print(inStart,reStart,leftLen);
		print(father+1,reStart+leftLen,length-1-leftLen);		//一定要画图，便于找到下标 
	}
	return ;
}


int main(void)
{
	scanf("%s",inorder);
	scanf("%s",reorder);
	print(0,0,strlen(inorder));
	return 0;
}
