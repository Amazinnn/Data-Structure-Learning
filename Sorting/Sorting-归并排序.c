/*归并排序*/
#include <stdio.h>

int n;


// 归并两个有序子数组
void merge(int *arr, int left, int mid, int right);

// 递归实现归并排序
void mergeSort(int *arr, int left, int right);

void Print(int *arr,int left,int right)
{
	for (int i=left;i<=right;i++){
		if (i) printf(" ");
		printf("%d",arr[i]);
	}
	printf("\n");
}

void merge(int *arr,int left,int mid,int right)
{
	printf("left=%d,mid=%d,right=%d\n",left,mid,right);
	if (left>=right) return ;
	int arr_new[right-left+1];
	int p1=left,p2=mid+1,p_new=0;
	while (p1<=mid&&p2<=right){
		if (arr[p1]<=arr[p2]){
			arr_new[p_new++]=arr[p1++];
		}
		else {
			arr_new[p_new++]=arr[p2++];
		}
	}
	while (p1<=mid)
		arr_new[p_new++]=arr[p1++];
	while (p2<=right)
		arr_new[p_new++]=arr[p2++];
	for (int i=0;i<right-left+1;i++){
		arr[i+left]=arr_new[i];
	}
	printf("Sorted array:\n");
	Print(arr,left,right);
	printf("The whole array:\n");
	Print(arr,0,n-1);
}

void mergeSort(int *arr, int left, int right)
{
	if (left>=right) return ;
	int mid=(left+right)/2;
	mergeSort(arr,left,mid);
	mergeSort(arr,mid+1,right);
	merge(arr,left,mid,right);
}

int main(void)
{
	scanf("%d",&n);
	int a[n];
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	mergeSort(a,0,n-1);
	printf("The answer is:\n");
	Print(a,0,n-1);
	return 0;
}




















