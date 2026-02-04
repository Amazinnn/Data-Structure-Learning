#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SplayNode {
    int size;
    struct SplayNode *left, *right;
} SplayNode;

SplayNode *Create(int k)
{
	SplayNode *NewNode=(SplayNode *)malloc(sizeof(SplayNode));
	NewNode->size=k;
	NewNode->left=NewNode->right=NULL;
	return NewNode;
}

SplayNode *LeftRotate(SplayNode *root)
{
	if (root==NULL||root->right==NULL) return root;
	SplayNode *SN1=root->right,*SN2=SN1->left;
	SN1->left=root;
	root->right=SN2;
	return SN1;
}

SplayNode *RightRotate(SplayNode *root)
{
	if (root==NULL||root->left==NULL) return root;
	SplayNode *SN1=root->left,*SN2=SN1->right;
	SN1->right=root;
	root->left=SN2;
	return SN1;
}

SplayNode *FindMin(SplayNode *root)
{
	if (root->left!=NULL) return root->left;
	else return root;
}

/*
        root
	   /   \
	ls		rs
   /  \    /  \
 ll   lr  rl   rr

*/

SplayNode *Splay(SplayNode *root,int k)
{
	if (root==NULL||root->size==k) return root;
	else if (k<root->size){
		SplayNode *ls=root->left;
		if (ls!=NULL){
			if (k<ls->size){
				ls->left=Splay(ls->left,k);
				ls=RightRotate(ls);
			}
			else if (k>ls->size){
				ls->right=Splay(ls->right,k);
				ls=LeftRotate(ls);
			}
			root=RightRotate(root);
		}
	}
	else {
		SplayNode *rs=root->right;
		if (rs!=NULL){
			if (k<rs->size){
				rs->left=Splay(rs->left,k);
				rs=RightRotate(rs);
			}
			else if (k>rs->size){
				rs->right=Splay(rs->right,k);
				rs=LeftRotate(rs);
			}
		}
		root=LeftRotate(root);
	}
	return root;
}

SplayNode *Insert(SplayNode *root,SplayNode *NewNode)
{
	int k=NewNode->size;
	if (root==NULL) return NewNode;
	else if (k<root->size){
		root->left=(root->left,NewNode);
		root->left=Splay(root->left,NewNode->size);
		root=RightRotate(root);
	}
	else if (k>root->size){
		root->right=(root->right,NewNode);
		root->right=Splay(root->right,NewNode->size);
		root=LeftRotate(root);
	}
	return root;
}

SplayNode *Delete(SplayNode *root,int k)
{
	if (root==NULL) return root;
	else root=Splay(root,k);
	if (root->size!=k) return root;
	else {
		if (root->right!=NULL){
			SplayNode *Front=FindMin(root->right),*RightSon;
			root->right=Splay(root->right,Front->size);
			RightSon=root->right;
			RightSon->left=root->left;
			free(root);
			return RightSon; 
		}
		else if (root->left!=NULL){
			SplayNode *LeftSon=root->left;
			free(root);
			return LeftSon;
		}
		else {
			free(root);
			return NULL;
		}
	}
}

SplayNode *Search(SplayNode *root, int k) {
    if (root == NULL || k == root->size) {
        if (root != NULL) root = Splay(root, k); // 找到后Splay
        return root;
    }
    if (k < root->size) 
        return Search(root->left, k);
    else 
        return Search(root->right, k);
}

void InOrderPrint(SplayNode *root)
{
	if (root==NULL) return ;
	InOrderPrint(root->left);
	printf("%d\n",root->size);
	InOrderPrint(root->right);
	return ;
}

int main() {
    SplayNode* root = NULL;
    int choice, value;
    SplayNode* result;
    
    printf("=== 伸展树交互测试程序 ===\n");
    
    while(1) {
        printf("\n请选择操作:\n");
        printf("1. 插入节点\n");
        printf("2. 删除节点\n");
        printf("3. 查找节点\n");
        printf("4. 中序遍历\n");
        printf("5. 清空树\n");
        printf("6. 退出\n");
        printf("请输入选择 (1-6): ");
        
        if(scanf("%d", &choice) != 1) {
            printf("输入无效，请重新输入！\n");
            while(getchar() != '\n'); // 清空输入缓冲区
            continue;
        }
        
        switch(choice) {
            case 1: {
                printf("请输入要插入的值: ");
                if(scanf("%d", &value) != 1) {
                    printf("输入无效！\n");
                    while(getchar() != '\n');
                    break;
                }
                
                // 检查值是否已存在
                if(Search(root, value) != NULL) {
                    printf("值 %d 已存在于树中！\n", value);
                } else {
                    SplayNode* newNode = Create(value);
                    root = Insert(root, newNode);
                    printf("值 %d 插入成功！\n", value);
                }
                break;
            }
            
            case 2: {
                printf("请输入要删除的值: ");
                if(scanf("%d", &value) != 1) {
                    printf("输入无效！\n");
                    while(getchar() != '\n');
                    break;
                }
                
                if(Search(root, value) == NULL) {
                    printf("值 %d 不存在于树中！\n", value);
                } else {
                    root = Delete(root, value);
                    printf("值 %d 删除成功！\n", value);
                }
                break;
            }
            
            case 3: {
                printf("请输入要查找的值: ");
                if(scanf("%d", &value) != 1) {
                    printf("输入无效！\n");
                    while(getchar() != '\n');
                    break;
                }
                
                result = Search(root, value);
                if(result != NULL) {
                    printf("值 %d 在树中找到！\n", value);
                    // 执行伸展操作，将找到的节点移到根节点
                    root = Splay(root, value);
                } else {
                    printf("值 %d 未在树中找到！\n", value);
                }
                break;
            }
            
            case 4: {
                if(root == NULL) {
                    printf("树为空！\n");
                } else {
                    printf("中序遍历结果: ");
                    InOrderPrint(root);
                    printf("\n");
                    printf("根节点值: %d\n", root->size);
                }
                break;
            }
            
            case 5: {
                // 简单的清空树方法：递归删除所有节点
                // 注意：这里使用了一个简化的方法，实际应该递归释放所有节点
                root = NULL;
                printf("树已清空！\n");
                break;
            }
            
            case 6: {
                printf("程序退出，感谢使用！\n");
                // 这里应该添加释放所有节点的代码
                return 0;
            }
            
            default: {
                printf("无效选择，请输入1-6之间的数字！\n");
                break;
            }
        }
    }
    
    return 0;
}













