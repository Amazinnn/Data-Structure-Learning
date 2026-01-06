/*
# P1732 [TJOI2011] 序列

## 题目描述

一数列 $A=\{a_1,a_2,\ldots,a_n\}$，
根据数列 $A$ 计算数列 $B=\{b_1,b_2,\ldots,b_n\}$，其中：  
$$
b_i=
\begin{cases}
a_1 &, i=1 \\ 
\min_{1 \leq j < i}\left|a_i-a_j\right| &, i\gt 1 
\end{cases}
$$
求 $\sum\limits^n_{i=1}b_i$。

## 输入格式

第一行是一个正整数 $T$，表示测试数据的组数。
接下来有 $T$ 行，每行表示一组测试数据。
每行以一个正整数 $n$ 开始，表示数列 $A$ 中元素的个数；
然后是 $n$ 个非负整数，依次表示 $a_1,a_2,\ldots,a_n$ 的值。

## 输出格式

对于每组测试数据，输出数列 $B$ 的所有的元素之和。

$1\le t\le 10$，$1\le n\le10^5$，$0\le a_i\le65536$。
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_M 65537  // 值域大小: 0 到 65536

typedef struct {
    int min_val;
    int max_val;
} Node;

Node tree[4 * MAX_M];  // 线段树数组

// 构建线段树，初始化最小值和最大值为-1
void build_tree(int idx, int l, int r) {
    tree[idx].min_val = -1;
    tree[idx].max_val = -1;
    if (l == r) return;
    int mid = (l + r) / 2;
    build_tree(2 * idx, l, mid);
    build_tree(2 * idx + 1, mid + 1, r);
}

// 更新线段树：在位置pos插入值
void update_tree(int idx, int l, int r, int pos) {
    if (l == r) {
        tree[idx].min_val = pos;
        tree[idx].max_val = pos;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update_tree(2 * idx, l, mid, pos);
    } else {
        update_tree(2 * idx + 1, mid + 1, r, pos);
    }

    int left_min = tree[2 * idx].min_val;
    int right_min = tree[2 * idx + 1].min_val;
    int left_max = tree[2 * idx].max_val;
    int right_max = tree[2 * idx + 1].max_val;

    if (left_min == -1) {
        tree[idx].min_val = right_min;
    } else if (right_min == -1) {
        tree[idx].min_val = left_min;
    } else {
        tree[idx].min_val = (left_min < right_min) ? left_min : right_min;
    }

    if (left_max == -1) {
        tree[idx].max_val = right_max;
    } else if (right_max == -1) {
        tree[idx].max_val = left_max;
    } else {
        tree[idx].max_val = (left_max > right_max) ? left_max : right_max;
    }
}

// 查询区间 [ql, qr] 的最大值
int query_max_range(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return -1;
    if (ql <= l && r <= qr) return tree[idx].max_val;
    int mid = (l + r) / 2;
    int left_max = -1, right_max = -1;
    if (ql <= mid) {
        left_max = query_max_range(2 * idx, l, mid, ql, qr);
    }
    if (qr > mid) {
        right_max = query_max_range(2 * idx + 1, mid + 1, r, ql, qr);
    }
    if (left_max == -1) return right_max;
    if (right_max == -1) return left_max;
    return (left_max > right_max) ? left_max : right_max;
}

// 查询区间 [ql, qr] 的最小值
int query_min_range(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return -1;
    if (ql <= l && r <= qr) return tree[idx].min_val;
    int mid = (l + r) / 2;
    int left_min = -1, right_min = -1;
    if (ql <= mid) {
        left_min = query_min_range(2 * idx, l, mid, ql, qr);
    }
    if (qr > mid) {
        right_min = query_min_range(2 * idx + 1, mid + 1, r, ql, qr);
    }
    if (left_min == -1) return right_min;
    if (right_min == -1) return left_min;
    return (left_min < right_min) ? left_min : right_min;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        // 初始化线段树，值域为0到MAX_M-1（即0到65536）
        build_tree(1, 0, MAX_M - 1);

        long long sum = 0;
        if (n > 0) {
            sum += a[0];  // 第一个元素的b_i即为a[0]
            update_tree(1, 0, MAX_M - 1, a[0]);  // 插入第一个元素
        }

        for (int i = 1; i < n; i++) {
            int pred = query_max_range(1, 0, MAX_M - 1, 0, a[i]);  // 前驱：小于等于a[i]的最大值
            int succ = query_min_range(1, 0, MAX_M - 1, a[i], MAX_M - 1);  // 后继：大于等于a[i]的最小值

            int diff = INT_MAX;
            if (pred != -1) {
                int d1 = a[i] - pred;
                if (d1 < diff) diff = d1;
            }
            if (succ != -1) {
                int d2 = succ - a[i];
                if (d2 < diff) diff = d2;
            }
            if (diff == INT_MAX) {
                // 理论上不会发生（因为至少有一个元素已插入），但为安全处理
                diff = 0;
            }
            sum += diff;
            update_tree(1, 0, MAX_M - 1, a[i]);  // 插入当前元素
        }
        printf("%lld\n", sum);
    }
    return 0;
}
