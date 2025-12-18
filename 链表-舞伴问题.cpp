/*

# P1878 舞蹈课
## 题目描述
有n个人参加一个舞蹈课。每个人的舞蹈技术由整数来决定。
在舞蹈课的开始，他们从左到右站成一排。
当这一排中至少有一对相邻的异性时，舞蹈技术相差最小的那一对会出列并开始跳舞。
如果不止一对，那么最左边的那一对出列。
一对异性出列之后，队伍中的空白按原顺序补上
（即：若队伍为 `ABCD`，那么 `BC` 出列之后队伍变为 `AD`）。
舞蹈技术相差最小即是 $a_i$ 的绝对值最小。
任务是模拟以上过程，确定跳舞的配对及顺序。

## 输入格式
第一行一个正整数 $n$ 表示队伍中的人数。
第二行包含 $n$ 个字符 `B` 或者 `G`，`B` 代表男，`G` 代表女。
第三行为 $n$ 个整数 $a_i$。所有信息按照从左到右的顺序给出。

## 输出格式
第一行一个整数表示出列的总对数 $k$。
接下来 $k$ 行，每行是两个整数。
按跳舞顺序输出，两个整数代表这一对舞伴的编号（按输入顺序从左往右 $1$ 至 $n$ 编号）。
请先输出较小的整数，再输出较大的整数。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    ll diff;
    int l, r;
} HeapNode;

static HeapNode *heapArr;
static int heapSize = 0;

static void heapSwap(int i, int j) {
    HeapNode t = heapArr[i];
    heapArr[i] = heapArr[j];
    heapArr[j] = t;
}

static int heapLess(const HeapNode *a, const HeapNode *b) {
    if (a->diff != b->diff) return a->diff < b->diff;
    return a->l < b->l;
}

static void heapPush(HeapNode node) {
    heapArr[++heapSize] = node;
    int i = heapSize;
    while (i > 1) {
        int p = i >> 1;
        if (heapLess(&heapArr[i], &heapArr[p])) {
            heapSwap(i, p);
            i = p;
        } else break;
    }
}

static HeapNode heapPop(void) {
    HeapNode ret = heapArr[1];
    heapArr[1] = heapArr[heapSize--];
    int i = 1;
    while (1) {
        int l = i << 1, r = l + 1, smallest = i;
        if (l <= heapSize && heapLess(&heapArr[l], &heapArr[smallest])) smallest = l;
        if (r <= heapSize && heapLess(&heapArr[r], &heapArr[smallest])) smallest = r;
        if (smallest != i) {
            heapSwap(i, smallest);
            i = smallest;
        } else break;
    }
    return ret;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1) return 0;
    char *g = (char*)malloc((n+2) * sizeof(char));
    if (!g) return 0;
    if (scanf("%s", g) != 1) { free(g); return 0; }

    ll *a = (ll*)malloc((n+1) * sizeof(ll));
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

    int *L = (int*)malloc((n+1) * sizeof(int));
    int *R = (int*)malloc((n+1) * sizeof(int));
    char *alive = (char*)malloc((n+1) * sizeof(char));
    for (int i = 1; i <= n; ++i) {
        L[i] = i - 1;
        R[i] = (i == n) ? 0 : i + 1;
        alive[i] = 1;
    }

    heapArr = (HeapNode*)malloc((n + 5) * sizeof(HeapNode));
    heapSize = 0;

    for (int i = 1; i <= n-1; ++i) {
        if (g[i-1] != g[i]) { // g string is 0-based
            ll diff = llabs(a[i] - a[i+1]);
            HeapNode node;
            node.diff = diff;
            node.l = i;
            node.r = i+1;
            heapPush(node);
        }
    }

    int cap = (n/2) + 4;
    int cnt = 0;
    int (*pairs)[2] = malloc(cap * sizeof *pairs);

    while (heapSize > 0) {
        HeapNode cur = heapPop();
        int l = cur.l, r = cur.r;
        if (l <= 0 || r <= 0) continue;
        if (!alive[l] || !alive[r]) continue;
        if (R[l] != r || L[r] != l) continue; // 已不是邻居，过期
        if (g[l-1] == g[r-1]) continue; // 性别变化，保险检查

        // 记录配对（按题目先小后大）
        int x = l < r ? l : r;
        int y = l < r ? r : l;
        if (cnt >= cap) {
            cap *= 2;
            pairs = realloc(pairs, cap * sizeof *pairs);
        }
        pairs[cnt][0] = x;
        pairs[cnt][1] = y;
        cnt++;

        // 删除 l 和 r
        alive[l] = alive[r] = 0;
        int LL = L[l];
        int RR = R[r];
        if (LL != 0) R[LL] = RR;
        if (RR != 0) L[RR] = LL;

        // 新的邻居对 (LL, RR)
        if (LL != 0 && RR != 0 && alive[LL] && alive[RR] && g[LL-1] != g[RR-1]) {
            ll diff = llabs(a[LL] - a[RR]);
            HeapNode node;
            node.diff = diff;
            node.l = LL;
            node.r = RR;
            heapPush(node);
        }
    }

    printf("%d\n", cnt);
    for (int i = 0; i < cnt; ++i) {
        printf("%d %d\n", pairs[i][0], pairs[i][1]);
    }

    free(pairs);
    free(heapArr);
    free(g);
    free(a);
    free(L);
    free(R);
    free(alive);
    return 0;
}