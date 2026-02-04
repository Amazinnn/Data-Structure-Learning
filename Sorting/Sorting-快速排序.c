#include <stdio.h>

void Swap(long int *a, long int *b)
{
    long int temp = *a;
    *a = *b;
    *b = temp;
}

void Print(long int *a, int n)
{
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%ld", a[i]);
    }
}

void QuickSort(long int *a, int n)
{
    if (n <= 1) return;

    int pivot = 0;				//也可以采用三数取中法将数组中间数移动到最左边，避免数组自然有序的最坏情况 
    int low = 0;
    int high = n - 1;
    long int temp = a[pivot]; // 基准值

    while (low < high) {
        // 先从右向左找小于等于基准的元素
        while (low < high && a[high] > temp) high--;
        if (low < high) {
            Swap(&a[low], &a[high]);
            low++; // 交换后左指针位置已处理，可后移
        }

        // 再从左向右找大于基准的元素
        while (low < high && a[low] <= temp) low++; // 注意这里改为 <=
        if (low < high) {
            Swap(&a[low], &a[high]);
            high--; // 交换后右指针位置已处理，可前移
        }
    }

    a[low] = temp; // 将基准值归位

    // 递归排序左右子数组
    QuickSort(a, low); // 左子数组：[0, low-1] 部分，长度为 low
    QuickSort(a + low + 1, n - low - 1); // 右子数组：[low+1, n-1]
}

int main(void)
{
    int length;
    scanf("%d", &length);
    long int set[length];
    for (int i = 0; i < length; i++) {
        scanf("%ld", &set[i]);
    }
    QuickSort(set, length);
    Print(set, length);
    return 0;
}
