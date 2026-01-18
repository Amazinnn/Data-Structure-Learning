/*
# P2580 于是他错误的点名开始了

## 题目背景

XS 中学化学竞赛组教练是一个酷爱炉石的人。

他会一边搓炉石一边点名以至于有一天他连续点到了某个同学两次，然后正好被路过的校长发现了然后就是一顿欧拉欧拉欧拉（详情请见已结束比赛 CON900）。

## 题目描述

这之后校长任命你为特派探员，每天记录他的点名。校长会提供化学竞赛学生的人数和名单，而你需要告诉校长他有没有点错名。（为什么不直接不让他玩炉石。）

## 输入格式

第一行一个整数 $n$，表示班上人数。

接下来 $n$ 行，每行一个字符串表示其名字（互不相同，且只含小写字母，长度不超过 $50$）。

第 $n+2$ 行一个整数 $m$，表示教练报的名字个数。

接下来 $m$ 行，每行一个字符串表示教练报的名字（只含小写字母，且长度不超过 $50$）。

## 输出格式

对于每个教练报的名字，输出一行。

如果该名字正确且是第一次出现，输出 `OK`，如果该名字错误，输出 `WRONG`，如果该名字正确但不是第一次出现，输出 `REPEAT`。

## 输入输出样例 #1

### 输入 #1

```
5  
a
b
c
ad
acd
3
a
a
e

```

### 输出 #1

```
OK
REPEAT
WRONG

```

## 说明/提示

- 对于 $40\%$ 的数据，$n\le 1000$，$m\le 2000$。
- 对于 $70\%$ 的数据，$n\le 10^4$，$m\le 2\times 10^4$。
- 对于 $100\%$ 的数据，$n\le 10^4$，$m≤10^5$。

---

$\text{upd 2022.7.30}$：新增加一组 Hack 数据。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_SIZE 100003  // 哈希表大小，选一个质数以减少冲突

// 哈希表节点结构
typedef struct Node {
    char *name;           // 存储名字字符串
    bool is_visited;      // 标记是否被点过名
    struct Node *next;    // 下一个节点指针
} Node;

// 哈希表结构
typedef struct {
    Node **buckets;       // 桶数组，每个桶是一个链表
    int size;            // 哈希表大小
} HashTable;

// 哈希函数：BKDRHash，适用于字符串
unsigned int hash_function(const char *str, int table_size) {
    unsigned int seed = 131; // 31, 131, 1313 等是常用乘数
    unsigned int hash = 0;
    while (*str) {
        hash = hash * seed + (*str++);
    }
    return hash % table_size;
}

// 初始化哈希表
HashTable *create_hash_table(int size) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->size = size;
    ht->buckets = (Node **)calloc(size, sizeof(Node *)); // 初始化为NULL
    return ht;
}

// 在哈希表中插入一个名字（初始状态为未访问）
void hash_table_insert(HashTable *ht, const char *name) {
    unsigned int index = hash_function(name, ht->size);
    Node *current = ht->buckets[index];
    
    // 检查是否已存在（题目说学生名字互不相同，但保险起见）
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return; // 已存在，直接返回
        }
        current = current->next;
    }
    
    // 创建新节点
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->name = (char *)malloc(strlen(name) + 1);
    strcpy(new_node->name, name);
    new_node->is_visited = false;
    new_node->next = ht->buckets[index]; // 头插法
    ht->buckets[index] = new_node;
}

// 在哈希表中查找名字，返回节点指针（如果找不到返回NULL）
Node *hash_table_find(HashTable *ht, const char *name) {
    unsigned int index = hash_function(name, ht->size);
    Node *current = ht->buckets[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 释放哈希表内存
void free_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        Node *current = ht->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
    free(ht->buckets);
    free(ht);
}

int main() {
    int n, m;
    scanf("%d", &n);
    
    // 创建哈希表
    HashTable *ht = create_hash_table(HASH_SIZE);
    
    // 读入学生名单并插入哈希表
    for (int i = 0; i < n; i++) {
        char name[51]; // 长度不超过50，加1用于结束符
        scanf("%s", name);
        hash_table_insert(ht, name);
    }
    
    scanf("%d", &m);
    
    // 处理点名
    for (int i = 0; i < m; i++) {
        char name[51];
        scanf("%s", name);
        Node *node = hash_table_find(ht, name);
        if (node == NULL) {
            printf("WRONG\n");
        } else {
            if (!node->is_visited) {
                printf("OK\n");
                node->is_visited = true;
            } else {
                printf("REPEAT\n");
            }
        }
    }
    
    // 释放内存
    free_hash_table(ht);
    return 0;
}
