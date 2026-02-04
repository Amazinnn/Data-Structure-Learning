/*»ùÊýÅÅÐò£¨LSD£©*/
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	long int data;
	struct node *next;
} node;

void Print(long int *arr,int n)
{
	for (int i=0;i<n;i++){
		if (i) printf(" ");
		printf("%ld",arr[i]);
	}
	printf("\n");
}

node *CreateNode(long int num)
{
	node *NewNode=(node *)malloc(sizeof(node));
	NewNode->data=num;
	NewNode->next=NULL;
	return NewNode;
}

int GetDigit(long int num,int pos)
{
	for (int i=1;i<=pos-1;i++)
		num/=10;
	return num%10;
}

int GetMaxDigits(long int *arr,int n)
{
	int max=1,digit;
	for (int i=0;i<n;i++){
		digit=0;
		int temp=arr[i];
		do {
			temp/=10;
			digit++;
		} while (temp);
		if (max<digit) max=digit;
	}
	return max;
}

void Free(node *list)
{
	node *curr=list,*prev;
	while (curr!=NULL){
		prev=curr;
		curr=curr->next;
		free(prev);
	}
}

void Append(node **Head,node **Tail,long int num)
{
	node *NewNode=CreateNode(num);
	if (*Head==NULL){
		*Head=*Tail=NewNode;
		return ;
	}
	(*Tail)->next=NewNode;
	*Tail=NewNode;
}

void RadixSort(long int *arr,int n)
{
	int MaxDigits=GetMaxDigits(arr,n);
	for (int i=1;i<=MaxDigits;i++){
		node *HeadBucket[10]={NULL},*TailBucket[10]={NULL};
		for (int j=0;j<n;j++){
			int digit=GetDigit(arr[j],i);
			Append(&HeadBucket[digit],&TailBucket[digit],arr[j]);
		}
		int j=0;
		for (int digit=0;digit<=9;digit++){
			node *curr=HeadBucket[digit];
			while (curr!=NULL){
				//printf("%d\n",j);
				arr[j++]=curr->data;
				curr=curr->next;
			}
			Free(HeadBucket[digit]);
		}
		Print(arr,n);
	}
}

int main(void)
{
	int n;
	scanf("%d",&n);
	long int PosiArr[n],NegaArr[n],TotalArr[n];
	int posi=0,nega=0;
	for (int i=0;i<n;i++){
		long int temp;
		scanf("%ld",&temp);
		if (temp>=0) PosiArr[posi++]=temp;
		else NegaArr[nega++]=-temp;
	}
	RadixSort(PosiArr,posi);
	RadixSort(NegaArr,nega);
	for (int i=0;i<n;i++){
		if (i<=nega-1) TotalArr[i]=-NegaArr[nega-i-1];
		else TotalArr[i]=PosiArr[i-nega];
	}
	Print(TotalArr,n);
	return 0;
}

