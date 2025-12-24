/*
P1827 [USACO3.4] 美国血统 American Heritage
农夫约翰非常认真地对待他的奶牛们的血统。
然而他不是一个真正优秀的记账员。
他把他的奶牛们的家谱作成二叉树，并且把二叉树以更线性的“树的中序遍历”
和“树的前序遍历”的符号加以记录而不是用图形的方法。

你的任务是在被给予奶牛家谱的“树中序遍历”和“树前序遍历”的符号后，
创建奶牛家谱的“树的后序遍历”的符号。每一头奶牛的姓名被译为一个唯一的字母。
（你可能已经知道你可以在知道树的两种遍历以后可以经常地重建这棵树。）
显然，这里的树不会有多于 26 个的顶点。

这是在样例输入和样例输出中的树的图形表达方式：

　　　　　　　　 C
　　　　　　   /  \
　　　　　　  /　　\
　　　　　　 B　　  G
　　　　　　/ \　　/
　　　　   A   D  H
　　　　　　  / \
　　　　　　 E   F

附注：
树的中序遍历是按照左子树，根，右子树的顺序访问节点；
树的前序遍历是按照根，左子树，右子树的顺序访问节点；
树的后序遍历是按照左子树，右子树，根的顺序访问节点。

输入格式
第一行一个字符串，表示该树的中序遍历。
第二行一个字符串，表示该树的前序遍历。

输出格式
单独的一行表示该树的后序遍历。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char preorder[27];						//前序遍历结果 
char inorder[27];						//中序遍历结果 

void prnPostOrder(int inStart,int preStart,int length)
{
	if (length==1){
		printf("%c",inorder[inStart]);
		return ;
	}
	else if (length==0) return ;						//子树长度为零，代表根本没有这个分支，故不操作。 
	char root=preorder[preStart];						//通过先序序列的首字母确定根节点 
	int inRoot;
	for (inRoot=inStart;inorder[inRoot]!=root&&inRoot<=inStart+length-1;inRoot++) ;		//找到根节点在中序遍历的位置（或者是分支的根节点的位置）
	int leftlen=inRoot-inStart;
	prnPostOrder(inStart,preStart+1,leftlen);			//先遍历左子树 
	prnPostOrder(inRoot+1,preStart+leftlen+1,length-1-leftlen);//再遍历右子树 
	printf("%c",root);									//最后打印根节点 
	return ;
}


int main(void)
{
	gets(inorder);
	gets(preorder);
	int len=strlen(inorder);
	prnPostOrder(0,0,len);								//第三个参数输入的是序列总长度，而非坐标，故 “len-1”有误！ 
	return 0;
}











