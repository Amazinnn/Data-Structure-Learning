/*堆排序*/
#include <stdio.h>

void Swap(long int *a,long int *b)
{
	long int temp=*a;
	*a=*b;
	*b=temp;
}

void Print(long int *a,int n)				//数组带有哨兵节点a[0]，总长度n，有效长度n-1 
{
	int sum=1,start=1;
	while (sum<n-1){
		for (int i=1;i<=start&&sum<=n-1;i++){
			printf("%6d",a[sum]);
			sum++;
		}
		start*=2;
		printf("\n");
	}
}

void Adjust(long int *a,int n,int curr)		//建立最大堆,n为实际长度，n-1为有效长度 
{
	if (n<=2) return ;
	for ( int i=2*curr ; i<n ; i*=2 ){
		if (i+1<n&&a[i]<a[i+1]) i+=1;
		if (a[i]<=a[curr]){
			break;
		}
		Swap(&a[i],&a[curr]);				//较小值通过父子交换，传递到子节点甚至树叶上 
		curr=i;
	}
}

void HeapSort(long int *a,int n)
{
	for (int i=(n+1)/2;i>=1;i--){
		Adjust(a,n,i);
	}
	for (int i=n-1;i>=1;i--){
		Swap(&a[1],&a[i]);
		Adjust(a,i,1);
	}
}

int main(void)
{
	int n;
	scanf("%d",&n);
	long int a[++n];				//n取实际长度 
	for (int i=1;i<=n-1;i++){
		scanf("%ld",&a[i]);
	}
	HeapSort(a,n);
	Print(a,n);
	return 0;
}

