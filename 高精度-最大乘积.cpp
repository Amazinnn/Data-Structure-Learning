/*
一个正整数一般可以分为几个互不相同的自然数的和，
如 3=1+2，4=1+3，5=1+4=2+3，6=1+5=2+4。

现在你的任务是将指定的正整数 n 分解成若干个互不相同的自然数
（也可以不分解，就是这个数字本身）的和，且使这些自然数的乘积最大。

输入格式
只有一个正整数 n，（3≤n≤10000）。
输出格式
第一行是分解方案，相邻的数之间用一个空格分开，并且按由小到大的顺序。

第二行是最大的乘积。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 10000  // 最大位数，应对大数乘积

// 大数结构，用于处理超大乘积
typedef struct {
    int digits[MAX_DIGITS];
    int len;
} BigNumber;

// 链表节点结构
typedef struct node {
    int fact;
    struct node *next;
} Node;

Node *MaxSet = NULL;
Node *Set = NULL;
BigNumber max_product = {0};

// 初始化大数为1
void initBigNumber(BigNumber *num) {
    memset(num->digits, 0, sizeof(num->digits));
    num->digits[0] = 1;
    num->len = 1;
}

// 大数乘法
void multiplyBigNumber(BigNumber *num, int factor) {
    int carry = 0;
    for (int i = 0; i < num->len; i++) {
        int product = num->digits[i] * factor + carry;
        num->digits[i] = product % 10;
        carry = product / 10;
    }
    while (carry) {
        num->digits[num->len] = carry % 10;
        carry /= 10;
        num->len++;
    }
}

// 比较两个大数的大小
int compareBigNumber(BigNumber *a, BigNumber *b) {
    if (a->len != b->len) {
        return a->len - b->len;
    }
    for (int i = a->len - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            return a->digits[i] - b->digits[i];
        }
    }
    return 0;
}

// 复制大数
void copyBigNumber(BigNumber *dest, BigNumber *src) {
    dest->len = src->len;
    memcpy(dest->digits, src->digits, sizeof(src->digits[0]) * src->len);
}

// 创建新节点
Node* createNode(int factor) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->fact = factor;
    newNode->next = NULL;
    return newNode;
}

// 清空链表（保留头节点）
void clearList(Node **head) {
    if (*head == NULL) return;
    
    Node *current = (*head)->next;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    (*head)->next = NULL;
}

// 复制链表
void copyList(Node **dest, Node **src) {
    clearList(dest);
    
    if (*src == NULL) {
        *dest = createNode(0); // 创建头节点
        return;
    }
    
    if (*dest == NULL) {
        *dest = createNode(0); // 创建头节点
    }
    
    Node *srcCurrent = (*src)->next;
    Node *destCurrent = *dest;
    
    while (srcCurrent != NULL) {
        Node *newNode = createNode(srcCurrent->fact);
        destCurrent->next = newNode;
        destCurrent = newNode;
        srcCurrent = srcCurrent->next;
    }
}

// 添加节点到链表
void addNode(Node **head, int factor) {
    if (*head == NULL) {
        *head = createNode(0); // 创建头节点
    }
    
    Node *newNode = createNode(factor);
    Node *current = *head;
    
    // 找到链表末尾
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
}

// 打印链表（分解方案）
void printList(Node *head) {
    if (head == NULL || head->next == NULL) {
        printf("%d\n", head != NULL ? head->fact : 0);
        return;
    }
    
    Node *current = head->next;
    while (current != NULL) {
        printf("%d", current->fact);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

// 打印大数
void printBigNumber(BigNumber *num) {
    for (int i = num->len - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}

// 计算当前链表的乘积（大数）
void calculateProduct(Node *head, BigNumber *product) {
    initBigNumber(product);
    
    if (head == NULL) return;
    
    Node *current = head->next;
    while (current != NULL) {
        multiplyBigNumber(product, current->fact);
        current = current->next;
    }
}

// 深度优先搜索函数
void findMaxProduct(int currentFactor, int remaining, Node **currentSet, BigNumber *currentProduct) {
    if (remaining == 0) {
        // 找到一个完整的分解方案
        BigNumber tempProduct;
        calculateProduct(*currentSet, &tempProduct);
        
        if (compareBigNumber(&tempProduct, &max_product) > 0) {
            copyBigNumber(&max_product, &tempProduct);
            copyList(&MaxSet, currentSet);
        }
        return;
    }
    
    if (remaining < currentFactor + 1) {
        return;
    }
    
    // 尝试所有可能的因子
    for (int i = currentFactor + 1; i <= remaining; i++) {
        addNode(currentSet, i);
        
        BigNumber newProduct;
        copyBigNumber(&newProduct, currentProduct);
        multiplyBigNumber(&newProduct, i);
        
        findMaxProduct(i, remaining - i, currentSet, &newProduct);
        
        // 回溯：移除刚才添加的节点
        if (*currentSet != NULL && (*currentSet)->next != NULL) {
            Node *last = *currentSet;
            while (last->next != NULL && last->next->next != NULL) {
                last = last->next;
            }
            if (last->next != NULL) {
                Node *temp = last->next;
                last->next = NULL;
                free(temp);
            }
        }
    }
}

// 释放链表内存
void freeList(Node **head) {
    if (*head == NULL) return;
    
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

int main(void) {
    int n;
    //printf("请输入正整数n (3≤n≤10000): ");
    scanf("%d", &n);
    
    if (n < 3 || n > 10000) {
        printf("输入错误！n必须在3到10000之间。\n");
        return 1;
    }
    
    // 初始化
    initBigNumber(&max_product);
    Set = createNode(0); // 创建头节点
    MaxSet = createNode(0); // 创建头节点
    
    BigNumber currentProduct;
    initBigNumber(&currentProduct);
    
    // 寻找最大乘积分解方案
    findMaxProduct(0, n, &Set, &currentProduct);
    
    // 输出结果
    //printf("分解方案: ");
    printList(MaxSet);
    
    //printf("最大乘积: ");
    printBigNumber(&max_product);
    
    // 释放内存
    freeList(&Set);
    freeList(&MaxSet);
    
    return 0;
}
