/*
题目描述
用高精度计算出 S=1!+2!+3!+?+n!（n≤50）。
其中 ! 表示阶乘，定义为 n!=n×(n?1)×(n?2)×?×1。例如，5!=5×4×3×2×1=120。

输入格式
一个正整数 n。
输出格式
一个正整数 S，表示计算结果。
*/

#include <stdio.h>

int func[10000][10000];				//从1到3248，得到的阶乘和有9998位 
int result[10000];

void fact(int m)					//计算m阶阶乘 
{
	if (m==1) return ;
	int add,front;
	add=0;
	for (int i=9999;i>=0;i--){
		front=m*func[m-1][i]+add;	//每一位数字均乘以n，然后多者进位 
		add=front/10;
		front%=10;
		func[m][i]=front;
	}
	return ;
}

void add(int m)						//将前m阶阶乘相加 
{
	int sum=0,add=0;
	int digit=9999;
	while (digit>=0){
		sum=add;
		for (int i=1;i<=m;i++){
			sum+=func[i][digit];
		}
		add=sum/10;					//进位操作 
		sum%=10;
		result[digit]=sum;
		digit--;
	}
	return ;
}

int main(void)
{
	func[1][9999]=1;
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		fact(i);
	}
	add(n);
	int start;
	for (start=0;result[start]==0;start++) ;
	printf("%d\n",9999-start+1);
	for (int i=start;i<=9999;i++) printf("%d",result[i]);
	return 0;
}
