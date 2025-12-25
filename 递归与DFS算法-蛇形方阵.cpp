/*
给出一个不大于 9 的正整数 n，输出 n×n 的蛇形方阵。
从左上角填上 1 开始，顺时针方向依次填入数字，如同样例所示。
注意每个数字有都会占用 3 个字符，前面使用空格补齐。

输入格式
输入一个正整数 n，含义如题所述。

输出格式
输出符合题目要求的蛇形矩阵。

  1  2  3  4
 12 13 14  5
 11 16 15  6
 10  9  8  7
*/
#include <stdio.h>
#include <stdbool.h>

typedef struct node{
	bool vacum;
	int num;
} node;
int n;
node a[100][100];
int curr=1;
int mode=0;
int dir[4][2]={0,1,1,0,0,-1,-1,0};

void move(int x,int y)
{
	//if (!a[y][x+1].vacum&&!a[y+1][x].vacum&&!a[y][x-1].vacum&&!a[y-1][x].vacum) return ;
	a[y][x].num=curr++;
	a[y][x].vacum=false;
	int xnew=x+dir[mode][1],ynew=y+dir[mode][0];
	if (!a[ynew][xnew].vacum){
		mode++;
		mode%=4;
		xnew=x+dir[mode][1],ynew=y+dir[mode][0];
	}
	if (!a[ynew][xnew].vacum) return;
	move(xnew,ynew);
	return ;
}

int main(void)
{
	scanf("%d",&n);
	for (int i=0;i<100;i++){
		for (int j=0;j<100;j++){
			if (i>=1&&i<=n&&j>=1&&j<=n){
				a[i][j].vacum=true;
			}
			else a[i][j].vacum=false;
		}
	}
	move(1,1);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			printf("%5d",a[i][j].num);
		}
		printf("\n");
	}
	return 0;
}
