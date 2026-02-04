#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum Red_Black{
	red,
	black
} Color;

typedef struct Red_Black_Tree{
	int data;
	Color color;
	struct Red_Black_Tree *left;
	struct Red_Black_Tree *right;
	struct Red_Black_Tree *parent;
} RBTree;

RBTree *FindUncle(RBTree *root)
{
	if (root==NULL||
		root->parent==NULL||
		root->parent->parent==NULL) 
		return NULL;
	RBTree *grandparent=root->parent->parent;
	if (grandparent->left==root->parent) 
		return grandparent->right;
	else 
		return grandparent->left;
}

RBTree *Create(int num)
{
	RBTree *NewNode=(RBTree *)malloc(sizeof(RBTree));
	NewNode->data=num;
	NewNode->color=red;
	NewNode->left=NewNode->right=NewNode->parent=NULL;
	return NewNode;
}

RBTree *Left(RBTree *node)
{
	if (node==NULL||node->right==NULL)
		return node;
	RBTree *rs=node->right;
	node->right=rs->left;
	if (rs->left!=NULL)
		rs->left->parent=node;
	rs->left=node;
	rs->parent=node->parent;
	node->parent=rs;
	return rs;
}

RBTree *Right(RBTree *node)
{
	if (node==NULL||node->left==NULL)
		return node;
	RBTree *ls=node->left;
	if (ls->right!=NULL)
		ls->right->parent=node;
	node->left=ls->right;
	ls->right=node;
	ls->parent=node->parent;
	node->parent=ls;
	return ls;
}

void ColorExchange(RBTree *A,RBTree *B)
{
	Color temp=A->color;
	A->color=B->color;
	B->color=temp;
}

RBTree *BSTInsert(RBTree *root,RBTree *NewNode)
{
	int num=NewNode->data;
	if (root==NULL) return NewNode;
	else if (num<root->data){
		root->left=BSTInsert(root->left,NewNode);
		root->left->parent=root;
	}
	else if(num>root->data){
		root->right=BSTInsert(root->right,NewNode);
		root->right->parent=root;
	}
	return root;
}

RBTree *InsertFix(RBTree *root,RBTree *node)
{
	while (node!=root&&
		node->color==red&&
		node->parent!=NULL&&
		node->parent->parent!=NULL&& 
		node->parent->color==red){
		RBTree *uncle=FindUncle(node),*father=node->parent;
		if (uncle!=NULL&&uncle->color==red){
			uncle->color=black;
			father->color=black;
			uncle->parent->color=red;
			node=uncle->parent;					//更新node至祖父节点位置 
		}
		else if (father==father->parent->left){
			if (node==father->right){
				node=Left(father);
			}
			node=Right(node->parent);
			ColorExchange(node,node->right);
		}
		else {
			if (node==father->left){
				node=Right(father);
			}
			node=Left(node->parent);
			ColorExchange(node,node->left);
		}
	}
	node->color=black;							//局部根节点为黑色 
	return root;
}

RBTree *Insert(RBTree *root,int num)
{
	RBTree *NewNode=Create(num);
	NewNode=BSTInsert(root,NewNode);
	root=InsertFix(root,NewNode);
	return root;
}













