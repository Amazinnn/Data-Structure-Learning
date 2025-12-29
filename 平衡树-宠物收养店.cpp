/*
# P2286 [HNOI2004] 宠物收养场

## 题目背景

题面修缮来自于 [LaDeX](https://www.luogu.com.cn/user/431658)。

## 题目描述

凡凡开了一间宠物收养场。收养场提供两种服务：收养被主人遗弃的宠物和让新的主人领养这些宠物。

每个领养者都希望领养到自己满意的宠物，凡凡根据领养者的要求通过他自己发明的一个特殊的公式，
得出该领养者希望领养的宠物的特点值 $a$（$a$ 是一个正整数，$a<2^{31}$），而他也给每个处在收养场的宠物一个特点值。
这样他就能够很方便的处理整个领养宠物的过程了，宠物收养场总是会有两种情况发生：
被遗弃的宠物过多或者是想要收养宠物的人太多，而宠物太少。

被遗弃的宠物过多时，假若到来一个领养者，这个领养者希望领养的宠物的特点值为 $a$，
那么它将会领养一只目前未被领养的宠物中特点值最接近 $a$ 的一只宠物。
（任何两只宠物的特点值都不可能是相同的，任何两个领养者的希望领养宠物的特点值也不可能是一样的）
如果有两只满足要求的宠物，即存在两只宠物他们的特点值分别为 $a-b$ 和 $a+b$，
那么领养者将会领养特点值为 $a-b$ 的那只宠物。

收养宠物的人过多，假若到来一只被收养的宠物，那么哪个领养者能够领养它呢？
能够领养它的领养者，是那个希望被领养宠物的特点值最接近该宠物特点值的领养者，
如果该宠物的特点值为 $a$，存在两个领养者他们希望领养宠物的特点值分别为 $a-b$ 和 $a+b$，
那么特点值为 $a-b$ 的那个领养者将成功领养该宠物。

一个领养者领养了一个特点值为 $a$ 的宠物，而它本身希望领养的宠物的特点值为 $b$，
那么这个领养者的不满意程度为 $|a-b|$。

你得到了一年当中，领养者和被收养宠物到来收养所的情况，
请你计算所有收养了宠物的领养者的不满意程度的总和。
这一年初始时，收养所里面既没有宠物，也没有领养者。

## 输入格式

第一行为一个正整数 $n$，$n\leq80000$，表示一年当中来到收养场的宠物和领养者的总数。
接下来的 $n$ 行，按到来时间的先后顺序描述了一年当中来到收养场的宠物和领养者的情况。
每行有两个正整数 $a,b$，其中 $a=0$ 表示宠物，$a=1$ 表示领养者，
$b$ 表示宠物的特点值或是领养者希望领养宠物的特点值。
（同一时间呆在收养所中的，要么全是宠物，要么全是领养者，这些宠物和领养者的个数不会超过 $10000$ 个）

## 输出格式

仅有一个正整数，表示一年当中所有收养了宠物的领养者的不满意程度的总和对 $1000000$ 取模以后的结果。

## 输入输出样例 #1

### 输入 #1

```
5                  
0 2                      
0 4                         
1 3
1 2
1 5
```

### 输出 #1

```
3
```

## 说明/提示

样例解释：

注：$|3-2| + |2-4|=3$，
最后一个领养者没有宠物可以领养。
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct pet{
	int height;
	long int num;
	bool adopted;
	struct pet *Left;
	struct pet *Right;
} pet;

pet *Root=NULL;

typedef struct customer{
	long int num;
	struct customer *next;
} customer;

customer *Head=NULL,*Tail=NULL;

pet *SinWithLeft(pet *root);
pet *SinWithRight(pet *root);
pet *DouWithLeft(pet *root);
pet *DouWithRight(pet *root);


int Max(int a,int b)
{
	return (a-b>=0)?a:b;
}

int Height(pet *node)
{
	if (node==NULL) return -1;			//不存在的节点的父节点一定为树叶节点 
	else return (node->height);
}


// 辅助函数：查找以给定节点为根的子树中的最大值节点（最右下节点）
pet* FindMax(pet* node) {
    if (node == NULL) return NULL;
    while (node->Right != NULL) {
        node = node->Right;
    }
    return node;
}

// 辅助函数：获取节点的平衡因子
int GetBalance(pet* node) {
    if (node == NULL) return 0;
    return Height(node->Left) - Height(node->Right);
}


pet* DeleteNode(pet* root, long int key) {
    // 1. 执行标准的BST删除
    if (root == NULL) return root;

    // 递归查找要删除的节点
    if (key < root->num) {
        root->Left = DeleteNode(root->Left, key);
    } else if (key > root->num) {
        root->Right = DeleteNode(root->Right, key);
    } else {
        // 找到要删除的节点
        // 情况1: 节点是叶子节点或只有一个子节点
        if ((root->Left == NULL) || (root->Right == NULL)) {
            pet* temp = root->Left ? root->Left : root->Right;
            
            // 没有子节点的情况
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { 
                // 有一个子节点的情况：用子节点直接替代当前节点
                *root = *temp; // 拷贝内容
            }
            free(temp);
        } else {
            // 情况2: 节点有两个子节点
            // 找到左子树中的最大值节点（前驱）
            pet* temp = FindMax(root->Left);
            // 用前驱的值替代当前节点的值
            root->num = temp->num;
            // 删除那个前驱节点（现在它变成了要删除的目标）
            root->Left = DeleteNode(root->Left, temp->num);
        }
    }

    // 如果树只有一个节点，删除后变为空树
    if (root == NULL) return root;

    // 2. 更新当前节点的高度
    root->height = Max(Height(root->Left), Height(root->Right)) + 1;

    // 3. 获取当前节点的平衡因子，检查是否失衡
    int balance = GetBalance(root);

    // 4. 如果不平衡，有四种情况需要处理

    // 左左情况 (LL)
    if (balance > 1 && GetBalance(root->Left) >= 0) {
        return SinWithLeft(root);
    }

    // 左右情况 (LR)
    if (balance > 1 && GetBalance(root->Left) < 0) {
        return DouWithLeft(root);
    }

    // 右右情况 (RR)
    if (balance < -1 && GetBalance(root->Right) <= 0) {
        return SinWithRight(root);
    }

    // 右左情况 (RL)
    if (balance < -1 && GetBalance(root->Right) > 0) {
        return DouWithRight(root);
    }

    // 如果仍然平衡，直接返回当前节点
    return root;
}


pet *SinWithLeft(pet *root)
{
	pet *k1,*k2;
	k1=root->Left;
	k2=k1->Right;
	k1->Right=root;
	root->Left=k2;
	root->height = Max(Height(root->Left), Height(root->Right)) + 1;
    k1->height = Max(Height(k1->Left), Height(k1->Right)) + 1;
	return k1;
}

pet *SinWithRight(pet *root)
{
	pet *k1,*k2;
	k1=root->Right;
	k2=root->Left;
	k1->Left=root;
	root->Right=k2;
	root->height = Max(Height(root->Left), Height(root->Right)) + 1;
    k1->height = Max(Height(k1->Left), Height(k1->Right)) + 1;
	return k1;
}

pet *DouWithLeft(pet *root)
{
	root->Left=SinWithRight(root->Left);
	root=SinWithLeft(root);
	return root;
}

pet *DouWithRight(pet *root)
{
	root->Right=SinWithLeft(root->Right);
	root=SinWithRight(root);
	return root;
}


pet *Insert(long int trait,pet *root)
{
	if (root==NULL){
		root=(pet *)malloc(sizeof(pet));
		root->adopted=0;
		root->Left=root->Right=NULL;
		root->num=trait;
	}
	else if (trait<root->num){
		root->Left=Insert(trait,root->Left);
		if (Height(root->Left)-Height(root->Right)==2){
			if (trait<root->Left->num){
			root=SinWithLeft(root);
			}
			else {
				root=DouWithLeft(root);
			}
		}
	}
	else if (trait>root->num){
		root->Right=Insert(trait,root->Right);
		if (Height(root->Right)-Height(root->Left)==2){
			if (trait>root->Right->num){
				root=SinWithRight(root);
			}
			else {
				root=DouWithRight(root);
			}
		}
	}
	else ;							//宠物已经在店里，无需再新增树叶（虽然本题无该情况） 
	root->height=Max(Height(root->Left),Height(root->Right))+1;
	return root;
}


// 查找最接近值并实际删除节点
long int FindAndRemove(pet** root, long int target) {
    if (*root == NULL) return -1;
    
    pet* current = *root;
    pet* parent = NULL;
    long int closest = (*root)->num;
    long int minDiff = labs(target - (*root)->num);
    
    pet* toDelete = *root;
    pet* parentToDelete = NULL;
    
    // 查找最接近的节点
    while (current != NULL) {
        long int currentDiff = labs(target - current->num);
        
        if (currentDiff < minDiff || 
            (currentDiff == minDiff && current->num < closest)) {
            minDiff = currentDiff;
            closest = current->num;
            toDelete = current;
            parentToDelete = parent;
        }
        
        parent = current;
        if (target < current->num) {
            current = current->Left;
        } else if (target > current->num) {
            current = current->Right;
        } else {
            toDelete = current;
            parentToDelete = parent;
            break;
        }
    }
    
    if (toDelete == NULL) return -1;
    
    // 关键修改：实际从树中删除节点，而不仅仅是标记
    *root = DeleteNode(*root, closest);
    
    return closest;
}




void Init(void)
{
	Head=(customer *)malloc(sizeof(customer));
	Head->next=NULL;
	Tail=Head;
	return ;
}


void WaitInQueue(long int trait)
{
	customer *temp=NULL;
	temp=(customer *)malloc(sizeof(customer));
	temp->num=trait;
	temp->next=NULL;
	Tail->next=temp;
	Tail=temp;
	return ;
}

long int PopCus(void)
{
	customer *dele=Head->next;
	Head->next=dele->next;
	if (dele==Tail) Tail=Head;
	long int result=dele->num;
	free(dele);
	return result;
}


int main(void)
{
	Init();
	long int n;
	long long int ans=0;
	scanf("%ld",&n);
	for (long int i=1;i<=n;i++){
		long int ManOrPet,trait;
		scanf("%ld %ld",&ManOrPet,&trait);
		getchar();
		if (ManOrPet==0){						//来了宠物 
			if (Head->next==NULL){
				printf("队列空，输入宠物%d\n",trait);
				Root=Insert(trait,Root);
			}
			else {
				long int Customer=PopCus();
				printf("队列有人，期望为%d的顾客直接买走%d\n",Customer,trait); 
				ans=(ans+labs(Customer-trait))%1000000;
			}
		}
		else {
			long int Pet=FindAndRemove(&Root,trait);		//找到并且送出 
			if (Pet==-1){
				printf("没有宠物，期望为%d顾客入队\n",trait);
				WaitInQueue(trait);
			}
			else {
				printf("找到宠物，期望为%d的顾客买走%d的宠物\n",trait,Pet);
				ans=(ans+labs(Pet-trait))%1000000;
			}
		}
	}
	printf("%lld",ans%1000000);
	return 0;
}














