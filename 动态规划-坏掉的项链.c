/*
USACO1.1 坏掉的项链 
你有一条由 n 个红色的，白色的，或蓝色的珠子组成的项链，珠子是随意安排的。这里是 n=29 的两个例子:
第一和第二个珠子在图片中已经被作记号。
图片 A 中的项链可以用下面的字符串表示：brbrrrbbbrrrrrbrrbbrbbbbrrrrb
假如你要在一些点打破项链，展开成一条直线，然后从一端开始收集同颜色的珠子直到你遇到一个不同的颜色珠子，
在另一端做同样的事（颜色可能与在这之前收集的不同）。 确定应该在哪里打破项链来收集到最大数目的珠子。
例如，在图片 A 中的项链中，在珠子 9 和珠子 10 或珠子 24 和珠子 25 之间打断项链可以收集到 8 个珠子。
表现含有白珠项链的字符串将会包括三个符号 r，b，w 。
写一个程序来确定从一条被给出的项链可以收集到的珠子最大数目。

在一些项链中还包括白色的珠子（如图片 B）所示。
当收集珠子的时候，一个被遇到的白色珠子可以被当做红色也可以被当做蓝色。

输入格式
第一行一个正整数 n，表示珠子数目。
第二行一串长度为 n 的字符串，每个字符是 r，b 或 w。
输出格式
输出一行一个整数，表示从给出的项链中可以收集到的珠子的最大数量。
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char ch;
    struct node *last;
    struct node *next;
} node;

typedef struct number {
    int sum;
    char ch;
    struct number *last;
    struct number *next;
} number;

// 修复change函数：处理白色珠子并将其转换为相邻颜色
node *change(char *p) {
    int len = strlen(p);
    if (len == 0) return NULL;
    
    node *head = NULL, *prev = NULL;
    
    // 创建双向循环链表
    for (int i = 0; i < len; i++) {
        node *temp = (node *)malloc(sizeof(node));
        temp->ch = p[i];
        temp->last = temp->next = NULL;
        
        if (head == NULL) {
            head = temp;
            prev = head;
        } else {
            prev->next = temp;
            temp->last = prev;
            prev = temp;
        }
    }
    
    // 连接首尾形成环形
    if (head && prev != head) {
        prev->next = head;
        head->last = prev;
    }
    
    // 处理白色珠子：将连续的白色珠子转换为相邻的非白色颜色
    node *current = head;
    do {
        if (current->ch == 'w') {
            // 找到第一个非白色珠子
            node *finder = current->next;
            char target_color = 'w';
            int found = 0;
            
            // 向后查找非白色珠子
            while (finder != current && !found) {
                if (finder->ch != 'w') {
                    target_color = finder->ch;
                    found = 1;
                }
                finder = finder->next;
            }
            
            // 如果向后没找到，向前查找
            if (!found) {
                finder = current->last;
                while (finder != current && !found) {
                    if (finder->ch != 'w') {
                        target_color = finder->ch;
                        found = 1;
                    }
                    finder = finder->last;
                }
            }
            
            // 如果整个项链都是白色，默认用'r'
            if (!found) target_color = 'r';
            
            // 转换连续的白色珠子
            node *start = current;
            while (current->ch == 'w') {
                current->ch = target_color;
                current = current->next;
            }
        } else {
            current = current->next;
        }
    } while (current != head);
    
    return head;
}

// 创建统计链表：统计连续相同颜色珠子的数量
number *create(node *head) {
    if (head == NULL) return NULL;
    
    number *head2 = NULL, *tail = NULL;
    node *current = head;
    
    do {
        char current_color = current->ch;
        int count = 0;
        node *start = current;
        
        // 统计连续相同颜色的珠子数量
        while (current->ch == current_color) {
            count++;
            current = current->next;
            if (current == start) break; // 防止无限循环
        }
        
        // 创建统计节点
        number *new_num = (number *)malloc(sizeof(number));
        new_num->sum = count;
        new_num->ch = current_color;
        new_num->last = new_num->next = NULL;
        
        if (head2 == NULL) {
            head2 = new_num;
            tail = new_num;
        } else {
            tail->next = new_num;
            new_num->last = tail;
            tail = new_num;
        }
        
    } while (current != head);
    
    // 连接首尾形成环形
    if (head2 && tail != head2) {
        tail->next = head2;
        head2->last = tail;
    }
    
    return head2;
}

// 计算最大收集珠子数量
int count(number *head2) {
    if (head2 == NULL) return 0;
    
    int max_count = 0;
    number *current = head2;
    
    do {
        // 尝试在每个间隙打破项链
        int total = current->sum;
        
        // 向前合并相同颜色的连续段（如果首尾颜色相同）
        if (current->last && current->last->ch == current->ch) {
            total += current->last->sum;
        }
        
        // 向后合并相同颜色的连续段
        if (current->next && current->next->ch == current->ch) {
            total += current->next->sum;
        }
        
        // 更新最大值
        if (total > max_count) {
            max_count = total;
        }
        
        current = current->next;
    } while (current != head2);
    
    // 确保不超过总珠子数
    number *temp = head2;
    int total_beads = 0;
    do {
        total_beads += temp->sum;
        temp = temp->next;
    } while (temp != head2);
    
    if (max_count > total_beads) {
        max_count = total_beads;
    }
    
    return max_count;
}

// 释放链表内存
void free_list(node *head) {
    if (head == NULL) return;
    
    node *current = head;
    do {
        node *next = current->next;
        free(current);
        current = next;
    } while (current != head);
}

void free_number_list(number *head) {
    if (head == NULL) return;
    
    number *current = head;
    do {
        number *next = current->next;
        free(current);
        current = next;
    } while (current != head);
}

int main(void) {
    int n;
    scanf("%d", &n);
    getchar(); // 读取换行符
    
    node *head = NULL;
    number *head2 = NULL;
    char s[1000];
    
    fgets(s, sizeof(s), stdin);
    // 去除换行符
    if (s[strlen(s)-1] == '\n') {
        s[strlen(s)-1] = '\0';
    }
    
    head = change(s);
    head2 = create(head);
    int num = count(head2);
    printf("%d\n", num);
    
    // 释放内存
    free_list(head);
    free_number_list(head2);
    
    return 0;
}
















