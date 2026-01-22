/*二叉堆(大根堆）*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long int *arr;
	int size;
	int capacity;
	
} Heap;

void Swap(long int *a,long int *b)
{
	long int temp=*a;
	*a=*b;
	*b=temp;
}

Heap *Create(void)
{
	Heap *heap=(Heap *)malloc(sizeof(Heap));
	heap->arr=(long int *)malloc(8*sizeof(long int));
	heap->size=0;
	heap->capacity=8;
	return heap;
}

void Free(Heap *heap)
{
	if (heap){
		if (heap->arr){
			free(heap->arr);
		}
		free(heap);
	}
}

void Resize(Heap *heap)			//数组大小翻倍
{
	long int *arr_new=heap->arr;
	arr_new=(long int *)realloc(heap->arr,2*heap->capacity*sizeof(long int));
	if (!arr_new){
		printf("扩容失败！\n");
		return ;
	}
	heap->arr=arr_new;
	heap->capacity*=2;
	return ;
}

void percolateUp(Heap *heap,int index)
{
	if (index<=0) return ;
	int parent;
	while (index){
		parent=(index-1)/2;
		if (heap->arr[parent]>=heap->arr[index])
			break;
		Swap(&(heap->arr[parent]),&(heap->arr[index]));
		index=parent;
	}
}

void percolateDown(Heap *heap,int index)
{
	int son;
	while (index*2+1<heap->size){
		son=index*2+1;
		if (son+1<heap->size&&heap->arr[son]<heap->arr[son+1])
			son++;
		if (heap->arr[index]>=heap->arr[son])
			break;
		Swap(&(heap->arr[index]),&(heap->arr[son]));
		index=son;
	}
}

void Push(Heap *heap,long int num)
{
	if (heap->size>=heap->capacity)
		Resize(heap);
	heap->arr[heap->size++]=num;
	percolateUp(heap,heap->size-1); 
}

void Pop(Heap *heap,long int *result)
{
	if (!heap->size){
		printf("堆已空，无弹出值。\n");
		return ;
	}
	Swap(&(heap->arr[0]),&(heap->arr[--heap->size]));
	*result=heap->arr[heap->size];
	percolateDown(heap,0);
	return ;
}

void BuildButtomToTop(Heap *heap,long int *arr,int length)
{
	while (heap->capacity<length)		//不能使用sizeof(arr),因为这样计算的是指针占用的字节！ 
		Resize(heap);
	for (int i=0;i<length;i++){
		heap->arr[i]=arr[i];
	}
	heap->size=length;
	for (int i=heap->size/2;i>=0;i--)
		percolateDown(heap,i);
}

void HeapSort(long int *arr,int length)
{
	Heap *heap=Create();
	BuildButtomToTop(heap,arr,length);
	for (int i=0;i<length;i++){
		Pop(heap,&arr[length-i-1]);
	}
	Free(heap);
}

void PrintHeap(Heap *heap) {
    if (heap->size == 0) {
        printf("堆为空\n");
        return;
    }
    
    printf("\n堆的金字塔结构 (size=%d, capacity=%d):\n", heap->size, heap->capacity);
    printf("========================================\n");
    
    // 计算堆的高度
    int height = 0;
    int temp = heap->size;
    while (temp > 0) {
        temp >>= 1;
        height++;
    }
    
    int level = 0;
    int nodesInCurrentLevel = 1;
    int printedCount = 0;
    
    // 打印每一层
    while (printedCount < heap->size) {
        // 计算当前层前面的空格数
        int spacesBefore = (1 << (height - level - 1)) - 1;
        
        // 打印前面的空格
        for (int i = 0; i < spacesBefore; i++) {
            printf("   ");
        }
        
        // 打印当前层的节点
        for (int i = 0; i < nodesInCurrentLevel && printedCount < heap->size; i++) {
            printf("%3ld", heap->arr[printedCount++]);
            
            // 计算节点之间的空格
            int spacesBetween = (1 << (height - level)) - 1;
            for (int j = 0; j < spacesBetween && i < nodesInCurrentLevel - 1 && printedCount < heap->size; j++) {
                printf("   ");
            }
        }
        
        printf("\n");
        
        // 更新到下一层
        level++;
        nodesInCurrentLevel *= 2;
    }
    printf("========================================\n\n");
}

int main() {
    printf("========== 大根堆测试程序 ==========\n\n");
    
    // 1. 测试创建堆
    printf("1. 测试创建堆\n");
    Heap *heap = Create();
    printf("创建堆成功，初始容量: %d\n\n", heap->capacity);
    
    // 2. 测试插入和扩容
    printf("2. 测试插入操作和动态扩容\n");
    printf("插入元素: ");
    for (int i = 1; i <= 20; i++) {
        Push(heap, i * 5);
        printf("%ld ", i * 5);
    }
    printf("\n");
    PrintHeap(heap);
    printf("当前容量: %d, 当前大小: %d\n\n", heap->capacity, heap->size);
    
    // 3. 测试弹出操作
    printf("3. 测试弹出操作\n");
    long int result;
    for (int i = 0; i < 5; i++) {
        Pop(heap, &result);
        printf("第%d次弹出: %ld\n", i+1, result);
    }
    PrintHeap(heap);
    printf("\n");
    
    // 4. 再插入一些元素
    printf("4. 再插入一些元素\n");
    Push(heap, 99);
    Push(heap, 33);
    Push(heap, 77);
    PrintHeap(heap);
    printf("\n");
    
    // 5. 批量建堆测试
    printf("5. 测试批量建堆\n");
    Heap *heap2 = Create();
    long int arr[] = {15, 3, 9, 7, 2, 8, 1, 4, 6, 5};
    int length = sizeof(arr) / sizeof(arr[0]);
    
    printf("原始数组: ");
    for (int i = 0; i < length; i++) {
        printf("%ld ", arr[i]);
    }
    printf("\n");
    
    BuildButtomToTop(heap2, arr, length);
    PrintHeap(heap2);
    
    // 验证批量建堆的结果
    printf("批量建堆后弹出顺序(从大到小): ");
    while (heap2->size > 0) {
        Pop(heap2, &result);
        printf("%ld ", result);
    }
    printf("\n\n");
    
    // 6. 测试堆排序
    printf("6. 测试堆排序\n");
    long int sort_arr[] = {15, 3, 9, 7, 2, 8, 1, 4, 6, 5};
    int sort_length = sizeof(sort_arr) / sizeof(sort_arr[0]);
    
    printf("排序前数组: ");
    for (int i = 0; i < sort_length; i++) {
        printf("%ld ", sort_arr[i]);
    }
    printf("\n");
    
    HeapSort(sort_arr, sort_length);
    
    printf("排序后数组(从大到小): ");
    for (int i = 0; i < sort_length; i++) {
        printf("%ld ", sort_arr[i]);
    }
    printf("\n\n");
    
    // 7. 边界情况测试
    printf("7. 边界情况测试\n");
    Heap *emptyHeap = Create();
    
    // 测试从空堆弹出
    printf("从空堆弹出: ");
    Pop(emptyHeap, &result);
    
    // 插入一个元素
    Push(emptyHeap, 100);
    printf("插入100后堆: ");
    PrintHeap(emptyHeap);
    
    // 弹出
    Pop(emptyHeap, &result);
    printf("弹出: %ld\n", result);
    printf("弹出后堆大小: %d\n\n", emptyHeap->size);
    
    // 8. 复杂操作测试
    printf("8. 复杂操作测试\n");
    Heap *complexHeap = Create();
    
    // 随机插入和弹出
    for (int i = 0; i < 10; i++) {
        long int val = rand() % 100;
        Push(complexHeap, val);
        printf("插入 %2ld -> ", val);
        PrintHeap(complexHeap);
        
        if (i % 3 == 0 && complexHeap->size > 0) {
            Pop(complexHeap, &result);
            printf("弹出 %2ld -> ", result);
            PrintHeap(complexHeap);
        }
    }
    
    // 最后全部弹出
    printf("\n最终全部弹出: ");
    while (complexHeap->size > 0) {
        Pop(complexHeap, &result);
        printf("%ld ", result);
    }
    printf("\n\n");
    
    // 9. 内存释放测试
    printf("9. 释放所有堆内存\n");
    Free(heap);
    Free(heap2);
    Free(emptyHeap);
    Free(complexHeap);
    
    printf("所有堆内存已释放\n");
    printf("测试完成!\n");
    
    return 0;
}


