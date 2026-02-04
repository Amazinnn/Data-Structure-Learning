/*Ï£¶ûÅÅÐò*/
#include <stdio.h>

int main(void)
{
	int n;
	scanf("%d",&n);
	long int a[n];
	for (int i=0;i<n;i++){
		scanf("%ld",&a[i]);
	}
	int dis=n/2;
	while (dis){
		for (int i=0;i<dis;i++){
			for (int j=1;dis*j+i<n;j++){
				int k;
				long int temp=a[dis*j+i];
				for (k=j-1;a[dis*k+i]>temp&&dis*k+i>=0;k--)
					a[dis*(k+1)+i]=a[dis*k+i];
				a[dis*(++k)+i]=temp;
			}
		}
		dis/=2;
	}
	for (int i=0;i<n;i++){
		if (i) printf(" ");
		printf("%ld",a[i]);
	}
	return 0;
}
