/*’€∞Î≈≈–Ú*/
#include <stdio.h>


void Print(long int *a,int n)
{
	for (int i=0;i<n;i++){
		if (i) printf(" ");
		printf("%ld",a[i]);
	}
	printf("\n");
	return ;
}


int main(void)
{
	int n;
	//printf("’€∞Î≈≈–Ú\n«Î ‰»Î ˝µƒ∏ˆ ˝£∫"); 
	scanf("%d",&n);
	long int a[n];
	for (int i=0;i<n;i++) scanf("%ld",&a[i]);
	
	long int low,high,mid;
	for (int i=1;i<n;i++){
		long int temp=a[i];
		low=0,high=i-1,mid=(low+high)/2;
		while (low<=high){
			if (temp>a[mid])
				low=mid+1;
			else
				high=mid-1;
			mid=(low+high)/2;
		}
		for (int j=i;j>=low;j--){
			a[j]=a[j-1];
		}
		a[low]=temp;
		//Print(a,n);
	}
	Print(a,n);
	return 0;
}
